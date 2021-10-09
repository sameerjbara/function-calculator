#include "FunctionCalculator.h"

#include "Sin.h"
#include "Ln.h"
#include "Poly.h"
#include "Mul.h"
#include "Add.h"
#include "Comp.h"
#include "Log.h"
#include <istream>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

FunctionCalculator::FunctionCalculator(std::istream& istr, std::ostream& ostr)
    : m_actions(createActions()), m_functions(createFunctions()), m_istr(istr), m_ostr(ostr)
{
}
FunctionCalculator::~FunctionCalculator()
{

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FunctionCalculator::run()
{
    m_ostr << std::setprecision(2) << std::fixed;
    do
    {   
        try
        {
            if (!m_isSizeGood)
            {
                m_ostr << "enter num of funvtion : [2,100] ";
                updateCurrentLine();
                checkinput(m_size);
                checkIfMoreArgs();
                checkSize(m_size);
            }
            m_ostr << '\n';
            printFunctions();
            m_ostr << "Enter command ('help' for the list of available commands): ";
            const auto action = readAction();
            runAction(action);
        }
        catch (const FewArguments&e)
        {
            cout << e.what();
        }
        catch (const WrongArgument&e)
        {
            cout << e.what();
        }
        catch (const MoreArguments& e)
        {
            cout << e.what();
        }
        catch (const NegativeArgument& e)
        {
            cout << e.what();
        }
        catch (InvalidPath e)//if the file is invalid
        {
            std::cerr << e.what();
        } 
        catch (const std::invalid_argument& e)//if the file is invalid
        {
            std::cerr << e.what();
        }
        catch (const std::runtime_error& e)//if the file is invalid
        {
            std::cerr << e.what();
        }
    } while (m_running);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool FunctionCalculator::checkToContinue()
{
    std::cout  <<
        "\nwould you like to continue to read "
        "the the file?\ny - yes / n - no\n";
        while (1)
        {
            try {
                string answer;
                std::getline(cin, answer);
                if (answer == "y")
                    return true;
                else if (answer == "n")
                    return false;
                else
                    throw std::istream::failure("");
            }
            catch (std::istream::failure e)
            {
                std::cout << "Bad input\nwould you like to continue to "
                    "read the the file ? \ny - yes / n - no\n";
            }
        }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FunctionCalculator::eval()
{
    int funm;
    if (!m_readMode)
    {
        updateCurrentLine();
    }
    checkinput(funm);
    if (auto i = readFunctionIndex(funm); i)
    {
        auto value = 0.;
        checkinput(value);
        checkIfMoreArgs();
        auto ans = (*m_functions[*i])(value);
        auto sstr = std::ostringstream();
        sstr << std::setprecision(2) << std::fixed << value;
        m_ostr << m_functions[*i]->to_string(sstr.str())
            << " = "
            << ans
            << '\n';
    }
 }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FunctionCalculator::updateCurrentLine()
{
     m_currentLine = (readLine());
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::stringstream FunctionCalculator::readLine()
{
    string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    return ss;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FunctionCalculator::poly()
{
    if (!m_readMode)
    {
        updateCurrentLine();
    }
    auto n = 0;
    checkinput(n);
    if (n < 0)
    {
        throw NegativeArgument();
    }
    auto coeffs = std::vector<double>(n);
    for (auto& coeff : coeffs)
    {
        checkinput(coeff);
        if (coeff < 0)
        {
            throw NegativeArgument();
        }
    }
    checkIfMoreArgs();
    m_functions.push_back(std::make_shared<Poly>(coeffs));
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FunctionCalculator::log()
{
    if (!m_readMode)
    {
        updateCurrentLine();
    }
    auto base = 0;
    int fnum;
    checkinput(base);
    checkinput(fnum);
    checkIfMoreArgs();
    if (auto f = readFunctionIndex(fnum); f)
    {
        m_functions.push_back(std::make_shared<Log>(base, m_functions[*f]));
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FunctionCalculator::del()
{
    int fnum;
    if (!m_readMode)
    {
        updateCurrentLine();
    }
    checkinput(fnum);   
    checkIfMoreArgs();
    if (auto i = readFunctionIndex(fnum); i)
    {
       m_functions.erase(m_functions.begin() + *i);
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FunctionCalculator::help()
{
    m_ostr << "The available commands are:\n";
    for (const auto& action : m_actions)
    {
        m_ostr << "* " << action.command << action.description << '\n';
    }
    m_ostr << '\n';
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FunctionCalculator::exit()
{
    m_ostr << "Goodbye!\n";
    m_running = false;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FunctionCalculator::printFunctions() const
{
    m_ostr << "List of available gates:\n";
    for (decltype(m_functions.size()) i = 0; i < m_functions.size(); ++i)
    {
        m_ostr << i << ".\t" << m_functions[i]->to_string("x") << '\n';
    }
    m_ostr << '\n';
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::optional<int> FunctionCalculator::readFunctionIndex(int i) const
{
    if (i >= m_functions.size())
    {
        throw WrongFucntion();
        return {};
    }
    return i;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FunctionCalculator::Action FunctionCalculator::readAction() const
{
    auto action = std::string();
    m_istr >> action;
    for (decltype(m_actions.size()) i = 0; i < m_actions.size(); ++i)
    {
        if (action == m_actions[i].command)
        {
            return m_actions[i].action;
        }
    }
    return Action::Invalid;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FunctionCalculator::runAction(Action action)
{
        switch (action)
        {
        default:
            throw invalid_argument("Unknown enum entry used!\n");
            break;

        case Action::Invalid:
            throw WrongCommand();
            break;

        case Action::Eval: 
            eval();            
            break;
        case Action::Poly: 
            poly();           
            break;
        case Action::Mul:  
            binaryFunc<Mul>();  
            break;
        case Action::Add:
            binaryFunc<Add>();
            break;
        case Action::Comp:
            binaryFunc<Comp>(); 
            break;
        case Action::Log: 
            log();              
            break;
        case Action::Resize: 
            resize();            
            break;
        case Action::Read:
            read();
            break;
        case Action::Del: 
            del();           
            break;
        case Action::Help:// 
            help();        
            break;
        case Action::Exit: //
            exit();          
            break;
        }
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FunctionCalculator::ActionMap FunctionCalculator::createActions()
{
    return ActionMap
    {
        {
            "eval",
            "(uate) num x - compute the result of function #num on x",
            Action::Eval
        },
        {
            "poly",
            "(nomial) N c_0 c_1 ... c_(N-1) - creates a polynomial with N coefficients",
            Action::Poly
        },
        {
            "mul",
            "(tiply) num1 num2 - Creates a function that is the multiplication of "
            "function #num1 and function #num2",
            Action::Mul
        },
        {
            "add",
            " num1 num2 - Creates a function that is the sum of function #num1 and "
            "function #num2",
            Action::Add
        },
        {
            "comp",
            "(osite) num1 num2 - creates a function that is the composition of "
            "function #num1 and function #num2",
            Action::Comp
        },
        {
            "log",
            " N num - create a function that is the log_N of function #num",
            Action::Log
        },
        {
            "resize",
            " size - change the size of the function to a new size",
            Action::Resize
        },
        {
            "read",
            " filename - read commands from file ",
            Action::Read
        },
        {
            "del",
            "(ete) num - delete function #num from the function list",
            Action::Del
        },
        {
            "help",
            " - print this command list",
            Action::Help
        },
        {
            "exit",
            " - exit the program",
            Action::Exit
        }
    };
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FunctionCalculator::FunctionList FunctionCalculator::createFunctions()
{
    return FunctionList
    {
        std::make_shared<Sin>(),
        std::make_shared<Ln>()
    };
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FunctionCalculator::checkIfMoreArgs()
{
    string s;
    m_currentLine >> s;
    if (!s.empty())//check if there are any more arguments
    {
        throw MoreArguments();
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FunctionCalculator::resize()
{
    size_t currentSize = m_functions.size();
   
    if (!m_readMode)
    {
        updateCurrentLine();
    }
    int newsize;
    checkinput(newsize);
    checkIfMoreArgs();
    checkSize(newsize);
    if (newsize < currentSize)
    {
        cout << "the new size is smaller than the original size , " << endl << "1-cancle the command " <<endl<<"2-continu and delete the last "
            << "funcitons "<<endl <<"(1/2)";
        if (!m_readMode)
        {
            updateCurrentLine();
        }
        int x;
        checkinput(x);
        if (x==2)
        {
            for (size_t index = newsize; index < currentSize; index++)
            {
                m_functions.pop_back();
            }
        }
    }
    else
    {
        setSize (newsize);
    } 
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FunctionCalculator::checkSize(int size)
{
    if (size < 2 || size>100)
    {
        throw std::invalid_argument("wrong range \n");
    }
    else
    {
        m_isSizeGood = true;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FunctionCalculator::read()
{
    bool valid = false;
    int lineCount=0;
    m_readMode = true;
    ifstream input;
    openFile(input); //open file

    m_currentLine = lineFromFile(input);
    auto action = std::string();
    while ((m_currentLine >> action)&& m_continueReading)
    {
        try
        {

            lineCount++;
            for (decltype(m_actions.size()) i = 0; i < m_actions.size(); ++i)
            {
                if (action == m_actions[i].command)
                {
                    valid = true;
                    runAction(m_actions[i].action);
                }
            }
            if (!valid)
            {
                runAction(Action::Invalid);
            }
            valid = false;
            m_currentLine = lineFromFile(input);


        }
        catch (const std::exception& e)
        {
             cout << "error in line " << lineCount << endl << e.what();
             m_continueReading = checkToContinue();
             m_currentLine = lineFromFile(input);

        }
    }
    m_readMode = false;
    input.close();
   
    
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FunctionCalculator::openFile(std::ifstream& input)
{
    updateCurrentLine();
    string path;
    m_currentLine >> path;
    input.open(path);
   if (!input.is_open())
       throw InvalidPath();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::stringstream FunctionCalculator::lineFromFile(std::ifstream& input)
{
    std::string line;
    std::getline(input, line);
    std::stringstream ss(line);
    return ss;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FunctionCalculator::checkIfCanAdd()
{
    if (m_functions.size() + 1 > m_size)
    {
        throw runtime_error("cant add more functions ");

    }
}