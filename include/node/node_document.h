#ifndef __node_document_h
#define __node_document_h

#include "node.h"

namespace iml
{
    class node_document : public node
    {
    private:
        std::list<node*> children;
    public:
        // Constructor and destructor
        node_document(std::list<node*>);
        ~node_document();

        void visualize(std::ostream&) const;
        std::list<double> evaluate() const;
    };
}

#endif