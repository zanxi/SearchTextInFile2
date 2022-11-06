// ConsoleApplicationThreadSafeQueue.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "thr_safe.h"
#include "Search.h"
#include "ReadingFile.h"
#include "Output.h"

unsigned const No_THREADS = 1;
unsigned const No_THREADS_con = 4;
unsigned const CO = 3;
string mask = "quali???t";
std::vector<std::thread> producers, consumers;
std::mutex cerrMutex;
string fname;
//std::atomic<int> xxxx(0);
//ThreadSafeQ<int> queue(6);
_SearchTextData queue_shd(50000);
map_InfoSearchStroki safe_ResultSearch;

int main(int argc, char** argv)
{

    setlocale(LC_ALL, "");

    if (argc > 1)// если передаем аргументы, то argc будет больше 1(в зависимости от кол-ва аргументов)
    {
        cout << argv[1] << endl;
        cout << argv[2] << endl;// вывод второй строки из массива указателей на строки(нумерация в строках начинается с 0 )

        fname = argv[1];
        mask = argv[2];
    }
    else
    {
        //cout << "Not arguments" << endl;
        //mask = "System.?o";
        //mask = "CAA";
        mask = "123";
        fname = "test5.txt";
        cout << "file: " << fname << " | mask: " << mask << '\n' << endl;
        //fname = "test2__.txt";
    }
    
    Reading(fname, queue_shd);
    // producers are creating
    for (unsigned i = 0; i < No_THREADS; ++i)
        producers.push_back(std::thread([&, i]() {
            // I/O locked
            {
                std::lock_guard<std::mutex> lock(cerrMutex);
                std::cerr << "THREAD #" << i << " pushing " << i * No_THREADS << " into Queue.\n";
            }
            ///queue.push(i*No_THREADS);                    
            //GetWorkStroki_Run("test3.txt", queue_shd);            
        }));
    // consumers are creating
    for (unsigned i = 0; i < No_THREADS_con; i++)
        consumers.push_back(std::thread([&, i]() {
        
        SearchTextData _searchtd;
        ThreadSafeQ<SearchTextData>::QueueResult result;
        while ((result = queue_shd.pop(_searchtd)) != ThreadSafeQ<SearchTextData>::CLOSED)
        {
            std::lock_guard<std::mutex> lock(cerrMutex);            
            FindSearch(mask, _searchtd, safe_ResultSearch);
        }
        // I/O locked
        {
            std::lock_guard<std::mutex> lock(cerrMutex);
            std::cerr << "<<< Finished find word >>>" << i << " is done.\n";
        }
            }));
    // Waiting for producers
    {
        std::lock_guard<std::mutex> lock(cerrMutex);
        std::cerr << "Search end !!!!!!!!!!!!.\n";
    }
    for (auto& t : producers)
        t.join();
    //  queue is closed
    {
        std::lock_guard<std::mutex> lock(cerrMutex);
        std::cerr << "Reading end !!!!!!!!!!!!.\n";
    }
    //queue.close();
    queue_shd.close();
    // Wait for consumers.
    {
        std::lock_guard<std::mutex> lock(cerrMutex);
        std::cerr << "Waiting for consumers...\n";
    }
    for (auto& t : consumers)
        t.join();



    // поиск строк завершен, удаляем обработчики
    std::cout << "\n\n\n SEARCH FINISHED .... Wait write result ..." << endl;
    std::this_thread::sleep_for(sleepTimerMain);
    if (safe_ResultSearch.size() != 0){
      // записываем в фйл
        OutPut(fname, mask, safe_ResultSearch);
        std::cout << "\n\n Found [" << safe_ResultSearch.size() << "] strok. RESULT SEARCH WRITE to OUTPUT.TXT" << endl;
    }
    else
    {
        cout << "\n\n RESULT SEARCH NOT FIND" << endl;
    }

    std::getchar();
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
