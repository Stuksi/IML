#ifndef __node_const_h
#define __node_const_h

#include "node.h"
#include <string>

namespace iml
{
    /// @brief Constant nodes, containing real numbers or strings.
    ///
    /// Leaf only nodes (do not have children).
    class node_const : public node
    {
    private:
        std::string value;
    public:
        //! Parameterized constructor of class node_const. Initializes the class value with a non-empty string.
        node_const(std::string);
        
        //! Visualizes the node by creating a visual tree node with the value in it. 
        void visualize(std::ostream&) const;
        /// Evaluates the node. If the value is a real number, returns the value by type convertion,
        /// otherwise the value is a string(capital-letter word) and a search for the value in the 
        /// parents of the node begins (if not defined in a previous link, an error message is thrown).
        std::list<double> evaluate() const;
    };
}

#endif