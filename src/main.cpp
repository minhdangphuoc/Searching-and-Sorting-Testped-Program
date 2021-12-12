#include <iostream>

#include "Utility.h"
#include "Order_list.h"
#include "RANDOM.H"
#include "TIMER.H"

namespace Program
{
   void main_1();
   void main_2();
   void main_3();
}

char options()
{
   char opt = NULL;
   while (opt == NULL || opt == '\n')
   {
      std::cout << "1.Run Group 1\n2.Run Group 2\n3.Run Group 3\n4.Run Group 4\n5.Run Group 5\n6.Quit the program\nYour choice: " << std::flush;
      opt = std::getchar();
   }

   if(system("CLS")) system("clear");
   return opt;
}


namespace Searching{
    // typedef List<Record> Ordered_list; 
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

    Error_code binary_search_1 (const Ordered_list &the_list,
                            const Key &target, int &position)
    /*
    Post: If a Record in the_list  has Key equal to target, then position locates
        one such entry and a code of success is returned.
        Otherwise, not_present is returned and position is undefined.
    Uses: Methods for classes List and Record.
    */
    {
        Record data;
        int bottom = 0, top = the_list.size() - 1;

        while (bottom < top) {
            int mid = (bottom + top) / 2;
            the_list.retrieve(mid, data);
            if (data < target)
                bottom = mid + 1;
            else
                top = mid;
        }
        if (top < bottom) return not_present;
        else {
            position = bottom;
            the_list.retrieve(bottom, data);
            if (data == target) return success;
            else return not_present;
        }
    }

    Error_code recursive_binary_2(const Ordered_list &the_list, const Key &target,
                              int bottom, int top, int &position)
    /*
    Pre:  The indices bottom to top define the
        range in the list to search for the target.
    Post: If a Record in the range from bottom to top in the_list
        has key equal to target, then position locates
        one such entry, and a code of success is returned.
        Otherwise, not_present is returned, and position is undefined.
    Uses: recursive_binary_2, together with methods from the classes
        Ordered_list and Record.
    */
    {
    Record data;
    if (bottom <= top) {
        int mid = (bottom + top) / 2;
        the_list.retrieve(mid, data);
        if (data == target) {
            position = mid;
            return success;
        }

        else if (data < target)
            return recursive_binary_2(the_list, target, mid + 1, top, position);
        else
            return recursive_binary_2(the_list, target, bottom, mid - 1, position);
    }
        else return not_present;
    }


    Error_code run_recursive_binary_2(const Ordered_list &the_list,
                                    const Key &target, int &position)
    {
        return recursive_binary_2(the_list, target, 0, the_list.size() - 1, position);
    }


    Error_code binary_search_2(const Ordered_list &the_list,
                            const Key &target, int &position)
    /*
    Post: If a Record in the_list has key equal to target, then position locates
        one such entry and a code of success is returned.
        Otherwise, not_present is returned and position is undefined.
    Uses: Methods for classes Ordered_list and Record.
    */
    {
    Record data;
    int bottom = 0, top = the_list.size() - 1;
    while (bottom <= top) {
        position = (bottom + top) / 2;
        the_list.retrieve(position, data);
        if (data == target) return success;
        if (data < target) bottom = position + 1;
        else top = position - 1;
    }
    return not_present;
    }
}

void print_out(std::string, const double &, const int &, const int &);

namespace Testing_1{
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
        std::cout << " Exiting test: " << std::endl
            << " The number of searches must be positive." << std::endl
            << " The number of list entries must exceed 0." << std::endl;
        return;
    }
    
    int i, target, found_at;
    Key::comparisons = 0;
    Random number; // Check this
    Timer clock; 

    // sequential_search:
    for (i = 0; i < searches; i++) {
        target = 2 * number.random_integer(0, list_size - 1) + 1; // 0 -> 18 + 1 = 1 -> 19, un increasing list
        if (Searching::sequential_search(the_list, target, found_at) == not_present) // 
            std::cout << "Error: Failed to find expected target " << target << std::endl; // 
    }
    
    print_out("Successful", clock.elapsed_time(), Key::comparisons, searches);

    Key::comparisons = 0;
    clock.reset();
    for (i = 0; i < searches; i++) {
        target = 2 * number.random_integer(0, list_size); // 0 -> 20 <= 0 -> 10
        if (Searching::sequential_search(the_list, target, found_at) == success)
            std::cout << "Error: Found unexpected target " << target
                << " at " << found_at << std::endl;
    }
    print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons, searches);
    }
}
namespace Testing_2{
    void test_search(int searches // What are looking for
                    , Ordered_list &the_list)
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
            std::cout << " Exiting test: " << std::endl
                << " The number of searches must be positive." << std::endl
                << " The number of list entries must exceed 0." << std::endl;
            return;
        }
        int i, found_at;
        Random number; // Check this
        Key::comparisons = 0;
        Timer clock; 
        int target_odd [searches];
        int target_even [searches];

        for (i = 0; i < searches; i++)
        {
            target_odd[i] = 2 * number.random_integer(0, list_size - 1) + 1; // 0 -> 18 + 1 = 1 -> 19, un increasing list
        }

        for (i = 0; i < searches; i++)
        {
            target_even[i] = 2 * number.random_integer(0, list_size); // 0 -> 20 <= 0 -> 10
        }

        // sequential_search:
        std::cout << "sequential_search:" << std::endl << "------------------" << std::endl;
        for (i = 0; i < searches; i++) {
            if (Searching::sequential_search(the_list, target_odd[i], found_at) == not_present) // 
                std::cout << "Error: Failed to find expected target " << target_odd[i] << std::endl; // 
        }
        

        print_out("Successful", clock.elapsed_time(), Key::comparisons, searches);

        Key::comparisons = 0;
        clock.reset();
        for (i = 0; i < searches; i++) {
            if (Searching::sequential_search(the_list, target_even[i], found_at) == success)
                std::cout << "Error: Found unexpected target " << target_even[i]
                    << " at " << found_at << std::endl;
        }
        print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons, searches);
        
        // run_recursive_binary_1:
        Key::comparisons = 0;
        clock.reset();
         std::cout << "run_recursive_binary_1:" << std::endl << "-----------------------" << std::endl;
        for (i = 0; i < searches; i++) {
            if (Searching::run_recursive_binary_1(the_list, target_odd[i], found_at) == not_present) // 
                std::cout << "Error: Failed to find expected target " << target_odd[i] << std::endl; // 
        }
        
        print_out("Successful", clock.elapsed_time(), Key::comparisons, searches);

        Key::comparisons = 0;
        clock.reset();
        for (i = 0; i < searches; i++) {
            if (Searching::run_recursive_binary_1(the_list, target_even[i], found_at) == success)
                std::cout << "Error: Found unexpected target " << target_even[i]
                    << " at " << found_at << std::endl;
        }
        print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons, searches);

        // binary_search_1:
        Key::comparisons = 0;
        clock.reset();
         std::cout << "binary_search_1:" << std::endl << "----------------" << std::endl;
        for (i = 0; i < searches; i++) {
            if (Searching::binary_search_1(the_list, target_odd[i], found_at) == not_present) // 
                std::cout << "Error: Failed to find expected target " << target_odd[i] << std::endl; // 
        }
        
        print_out("Successful", clock.elapsed_time(), Key::comparisons, searches);

        Key::comparisons = 0;
        clock.reset();
        for (i = 0; i < searches; i++) {
            if (Searching::binary_search_1(the_list, target_even[i], found_at) == success)
                std::cout << "Error: Found unexpected target " << target_even[i]
                    << " at " << found_at << std::endl;
        }
        print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons, searches);

        // run_recursive_binary_2:
        Key::comparisons = 0;
        clock.reset();
         std::cout << "run_recursive_binary_2:" << std::endl << "-----------------------" << std::endl;
        for (i = 0; i < searches; i++) {
            if (Searching::run_recursive_binary_2(the_list, target_odd[i], found_at) == not_present) // 
                std::cout << "Error: Failed to find expected target " << target_odd[i] << std::endl; // 
        }
        
        print_out("Successful", clock.elapsed_time(), Key::comparisons, searches);

        Key::comparisons = 0;
        clock.reset();
        for (i = 0; i < searches; i++) {
            if (Searching::run_recursive_binary_2(the_list, target_even[i], found_at) == success)
                std::cout << "Error: Found unexpected target " << target_even[i]
                    << " at " << found_at << std::endl;
        }
        print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons, searches);
        
        // binary_search_2:
        Key::comparisons = 0;
        clock.reset();
         std::cout << "binary_search_2:" << std::endl << "----------------" << std::endl;
        for (i = 0; i < searches; i++) {
            if (Searching::binary_search_2(the_list, target_odd[i], found_at) == not_present) // 
                std::cout << "Error: Failed to find expected target " << target_odd[i] << std::endl; // 
        }
        
        print_out("Successful", clock.elapsed_time(), Key::comparisons, searches);

        Key::comparisons = 0;
        clock.reset();
        for (i = 0; i < searches; i++) {
            if (Searching::binary_search_2(the_list, target_even[i], found_at) == success)
                std::cout << "Error: Found unexpected target " << target_even[i]
                    << " at " << found_at << std::endl;
        }
        print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons, searches);
    }
}

void Program :: main_1()
{
    List<Record> TestList;
    Key * key;
    // Random num;
    int in = 0, pos = 0;
    int max_num = 0;
    std::cout << "Input size: ";
    std::cin >> in;
    max_num = in;
    for (int i = 0; i < in; i++){
        // key = new Key(2 * num.random_integer(0, 9) + 1); // 1 -> 19
        key = new Key(2 * i + 1); // 1 -> 19
        TestList.insert(i, *key);
        delete key;
    }
    Testing_1::test_search(in, TestList);
}

void Program :: main_2()
{
    Ordered_list TestList;
    Key * key;
    // Random num;
    int in = 0, pos = 0, s;
    int max_num = 0;
    
    std::cout << "Input size: ";
    std::cin >> in;
    max_num = in;

    std::cout << "Input size: ";
    std::cin >> in;
    s = in;
    
    for (int i = 0; i < max_num; i++){
        // key = new Key(2 * num.random_integer(0, 9) + 1); // 1 -> 19
        key = new Key(2 * i + 1); // 1 -> 19
        TestList.insert(i, *key);
        delete key;
    }
    Testing_2::test_search(s, TestList);
}

void Program :: main_3()
{
    
}

int main() {
    switch(options())
    {
        case '1':
            Program::main_1();
            break;
        case '2':
            Program::main_2();
            break;
        case '3':
            Program::main_3();
            break;
        default:
            std::cout << "Wrong input, exit program." << std::endl;
    }
}

void print_out(std::string msg, const double & time, const int & comparisons, const int & searches)
{
    std::cout.precision(7);
    std::cout << "Status: " << msg << std::endl
            << "Elapsed per search: " <<  std::fixed << time << std::endl
            << "Compairisons per search: " << comparisons << std::endl
            << "Searches: " << searches << std::endl << std::endl;
}