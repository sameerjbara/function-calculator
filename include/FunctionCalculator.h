#pragma once

#include <vector>
#include <memory>
#include <string>
#include <iosfwd>
#include <optional>
#include <sstream>
#include <sstream>
#include "Exceptions.h"


class Function;

class FunctionCalculator
{
public:
    FunctionCalculator(std::istream& istr, std::ostream& ostr);
    ~FunctionCalculator();
    void run();

private:
    int m_errorLine;
    size_t m_size = 0;
    std::stringstream m_currentLine;
    bool m_readMode = false;
    bool m_continueReading = true;
    bool m_isSizeGood = false;


    bool checkToContinue();

    std::stringstream readLine();
    std::stringstream lineFromFile(std::ifstream& input);

    void checkIfCanAdd();
    void updateCurrentLine();
    void eval();
    void poly();
    void log();
    void del();
    void help();
    void exit();
    void resize();
    void read();
    void openFile(std::ifstream& input);
    void checkSize(int size);
    void checkIfMoreArgs();
    void setSize(size_t newSize)
    {
        m_size = newSize;
    }
    

    

    template <typename FuncType>
    void binaryFunc()
    {
        if (!m_readMode)
        {
            updateCurrentLine();
        }
        checkIfCanAdd();

        int x1,x2;
        checkinput(x1);
        checkinput(x2);
        checkIfMoreArgs();
        if (auto f0 = readFunctionIndex(x1), f1 = readFunctionIndex(x2); f0 && f1)
        {

           m_functions.push_back(std::make_shared<FuncType>(m_functions[*f0], m_functions[*f1]));
        }
        
    }

    void printFunctions() const;

    enum class Action
    {
        Invalid,
        Eval,
        Poly,
        Mul,
        Add,
        Comp,
        Log,
        Resize,
        Read,
        Del,
        Help,
        Exit,
    };

    struct ActionDetails
    {
        std::string command;
        std::string description;
        Action action;
    };

    using ActionMap = std::vector<ActionDetails>;
    using FunctionList = std::vector<std::shared_ptr<Function>>;

    const ActionMap m_actions;
    FunctionList m_functions;
    bool m_running = true;
    std::istream& m_istr;
    std::ostream& m_ostr;

    std::optional<int> readFunctionIndex(int i) const;
    Action readAction() const;
    void runAction(Action action);

    static ActionMap createActions();
    static FunctionList createFunctions();

    template <class T>
    void checkinput( T& t) 
    {
        while ((m_currentLine.peek()) == ' ' && m_currentLine.peek() != EOF && m_currentLine.peek() != '\n') {
            m_currentLine.ignore(1);
        }
        if (m_currentLine.peek() == EOF)
        {
            throw FewArguments();
        }
        else if(isalpha(m_currentLine.peek()))
        { 
            throw WrongArgument();
        }
        else
        {
            m_currentLine >> t;
        }
    }
};
