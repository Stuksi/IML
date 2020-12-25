#ifndef __node_tag_h
#define __node_tag_h

#include "node.h"
#include "../tag/tag.h"

namespace iml
{
    class node_tag : public node
    {
    private:
        tag* tag_;
        std::list<node*> children_;
    public:
        node_tag();
        node_tag(tag*, std::list<node*>);
        ~node_tag();

        void visualize(std::ostream&) const;
        std::list<double> evaluate() const;
    };
}

#endif