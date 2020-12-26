#include <cstring>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <random>
#include <thread>
#include <type_traits>
#include <vector>

using namespace tx;
using namespace std;
using namespace std::chrono_literals;

struct test_item;

using item_list = std::vector<test_item>;
using index_list = std::vector<size_t>;

using entropy = random_device;
using prn_gen = mt19937_64;
using int_dist = uniform_int_distribution<>;
using hasher = std::hash<std::string_view>;

struct test_item : public lockable_item
{
    static constexpr size_t buf_size = 32;
    char ma_chars[buf_size];

    void st_update(FILE * fp, prn_gen &  gen, int_dist & char_dist);
    void tx_update(transaction const & tx, FILE * fp, prn_gen & gen, int_dist & char_dist);
};

// Update on-board data for single threaded updates. Checks to see if a race has occurred.

void
test_item::st_update(FILE *fp, prn_gen &gen, int_dist &char_dist)
{
    char         local_chars[buf_size];
    string_view  local_view(local_chars, buf_size);
    string_view  shared_view(ma_chars, buf_size);
    hasher       hash;

    for ( size_t i = 0; i < buf_size; ++i)
    {
        local_chars[i] = ma_chars[i] = (char) char_dist(gen);
    }

    if (hash(shared_view) != hash(local_view))
    {
        fprintf(fp, "Race found!, item %zd\n", this->id());
    }
}

// Updates on-board for the STO tests. Checks to see if the race has occurred
void test_item::tx_update(transaction const &tx, FILE *fp, prn_gen &gen, int_dist &char_dist) {
    char        local_chars[buf_size];
    string_view local_view(local_chars, buf_size);
    string_view shared_view(ma_chars, buf_size);

    for ( size_t i = 0; i < buf_size; ++i)
    {
        local_chars[i] = ma_chars[i] = (char) char_dist(gen);
    }

    if (hash(shared_view) != hash(local_view))
    {
        fprintf(fp, "RACE FOUND!, TX %zd item %zd\n", tx.id(), this->id());
    }
}

void tx_access_test(item_list & items, FILE * fp, size_t tx_count, size_t refs_count)
{
    entropy rd;
    prn_gen gen(rd());
    int_dist refs_index_dist(0, (int) (items.size() - 1));
    int_dist refs_count_dist(1, (int) refs_count);
    int_dist char_dist(0, 127);

    stopwatch  sw;
    index_list indices;
    size_t     index;

    transaction_manager tx(1, fp);
    bool                acquired;

    sw.start();

    for( size_t i = 0; i < tx_count; ++i ) {
        // compute the size of the update group
        indices.clear();
        refs_count = refs_count_dist(gen);

        // compute the membership of the update group
        for (size_t j = 0; j < refs_count; ++j) {
            index = refs_index_dist(gen);
            indices.push_back(index);
        }

        tx.begin();
        acquired = true;

        // Acquire the members of update group
        for (size_t j = 0; acquired && j < refs_count; ++j) {
            index = indices[j];
            acquired = tx.acquire(items[index]);
        }

        if (acquired) {
            for (size_t j = 0; j < refs_count; ++j) {
                index = indices[j];
                items[index].tx_update(tx, fp, gen, char_dist);
            }
            tx.commit();
        } else {
            tx.rollback();
        }

    }
    sw.stop();
    fprintf(fp, "TX %zd took %d msec\n", tx.id(), sw.milliseconds_elapsed<int>());
}