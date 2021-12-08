#include <iostream>

#include "Utility.h"
#include "Record.h"
#include "List.h"
#include "RANDOM.H"
#include "TIMER.H"

typedef Key Record;

namespace Searching{
    typedef List<Record> Ordered_list; 
    Error_code sequential_search(const List<Record> &the_list,
                                const Key &target, int &position)
    /*
    Post: If an entry in the_list has key equal to target, then return
        success and the output parameter position locates such an entry
        within the list.
        Otherwise return not_present and position becomes invalid.
    */
    {
        int s = the_list.size();
        for (position = 0; position < s; position++) {
            Record data; // new key
            the_list.retrieve(position, data); //
            if (data == target) return success; // in the list, there is a key equal with target :: Operator == key:: compare ++
        }
        return not_present;
    }

    Error_code recursive_binary_1(const Ordered_list &the_list, const Key &target,
                              int bottom, int top, int &position)
    /*
    Pre:  The indices bottom to top define the
        range in the list to search for the target.
    Post: If a Record in the range of locations
        from bottom to top in the_list has key equal
        to target, then position locates
        one such entry and a code of success is returned.
        Otherwise, the Error_code of not_present is returned
        and position becomes undefined.
    Uses: recursive_binary_1 and methods of the classes List and Record.
    */
    {
    Record data;
    if (bottom < top) {              // List has more than one entry.
        int mid = (bottom + top) / 2;
        the_list.retrieve(mid, data);
        if (data < target)  // Reduce to top half of list.
            return recursive_binary_1(the_list, target, mid + 1, top, position);
        else                          // Reduce to bottom half of list.
            return recursive_binary_1(the_list, target, bottom, mid, position);
    }
    else if (top < bottom)
        return not_present;           // List is empty.
    else {                           // List has exactly one entry.
        position = bottom;
        the_list.retrieve(bottom, data);
        if (data == target) return success;
        else return not_present;
    }
    }


    Error_code run_recursive_binary_1(const Ordered_list &the_list,
                                    const Key &target, int &position)
    {
    return recursive_binary_1(the_list, target, 0, the_list.size() - 1, position);
    }

}

namespace Testing{

    void print_out(std::string, const double &, const int &, const int &);

    
    void test_search(int searches // What are looking for
                    , List<Record> &the_list)
    /*

    Pre:  None.
    Post: The number of key comparisons and CPU time for a
        sequential searching function have been calculated.
    Uses: Methods of the classes List, Random, and Timer,
        together with an output function print_out
    */
    {

    int list_size = the_list.size(); // Unknow list
    if (searches <= 0 || list_size < 0) {
        cout << " Exiting test: " << endl
            << " The number of searches must be positive." << endl
            << " The number of list entries must exceed 0." << endl;
        return;
    }
    int i, target, found_at;
    Key::comparisons = 0;
    Random number; // Check this
    Timer clock; 

    // sequential_search:
    std::cout << "sequential_search:" << std::endl << "------------------" << std::endl;
    for (i = 0; i < searches; i++) {
        target = 2 * number.random_integer(0, list_size - 1) + 1; // 0 -> 18 + 1 = 1 -> 19, un increasing list
        std::cout << target << " ";
        if (Searching::sequential_search(the_list, target, found_at) == not_present) // 
            cout << "Error: Failed to find expected target " << target << endl; // 
    }
    std::cout << std::endl;
    print_out("Successful", clock.elapsed_time(), Key::comparisons, searches);

    Key::comparisons = 0;
    clock.reset();
    for (i = 0; i < searches; i++) {
        target = 2 * number.random_integer(0, list_size); // 0 -> 20 <= 0 -> 10
        if (Searching::sequential_search(the_list, target, found_at) == success)
            cout << "Error: Found unexpected target " << target
                << " at " << found_at << endl;
    }
    print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons, searches);
    
    // run_recursive_binary_1:
    std::cout << "run_recursive_binary_1:" << std::endl << "-----------------------" << std::endl;
    for (i = 0; i < searches; i++) {
        target = 2 * number.random_integer(0, list_size - 1) + 1; // 0 -> 18 + 1 = 1 -> 19, un increasing list
        std::cout << target << " ";
        if (Searching::run_recursive_binary_1(the_list, target, found_at) == not_present) // 
            cout << "Error: Failed to find expected target " << target << endl; // 
    }
    std::cout << std::endl;
    print_out("Successful", clock.elapsed_time(), Key::comparisons, searches);

    Key::comparisons = 0;
    clock.reset();
    for (i = 0; i < searches; i++) {
        target = 2 * number.random_integer(0, list_size); // 0 -> 20 <= 0 -> 10
        if (Searching::run_recursive_binary_1(the_list, target, found_at) == success)
            cout << "Error: Found unexpected target " << target
                << " at " << found_at << endl;
    }
    print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons, searches);
    
    }
}

int main()
{
    List<Key> TestList;
    Key * key;
    Random num;
    int in = 0, pos = 0;
    int max_num = 0;
    std::cout << "Input size: ";
    std::cin >> in;
    max_num = in;
    for (int i = 0; i < in; i++){
        key = new Key(2 * num.random_integer(0, 9) + 1); // 1 -> 19
        TestList.insert(i, *key);
        delete key;
    }
    Testing::test_search(in, TestList);
}

void Testing::print_out(std::string msg, const double & time, const int & comparisons, const int & searches)
{
    std::cout.precision(6);
    std::cout << "Status: " << msg << std::endl
            << "Elapsed per search: " <<  std::fixed << time << std::endl
            << "Compairisons per search: " << comparisons << std::endl
            << "Searches: " << searches << std::endl << std::endl;
}