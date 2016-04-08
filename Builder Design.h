#include <QDebug>

#include <memory>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
#ifndef BUILDER_H
#define BUILDER_H

class builder
{
public:
    builder();

    ostringstream qts;

    struct HtmlElement
    {

        string name;
        string text;
        vector<HtmlElement> elements;
        const size_t indent_size = 2;

        HtmlElement(){}

        HtmlElement(const string& name, const string& text)
        {
           this->name = name;
            this->text = text;
        }

        string str(int indent = 0) const
        {
            ostringstream oss;
            string i(indent_size * indent, ' ');
            oss << i << "<" << name << ">" << endl;

            if(text.size() > 0){
                oss << string(indent_size * (indent + 1), ' ') << text << endl;
            }
            for(const auto& e: elements){
                oss << e.str(indent + 1);
            }
            oss << i << "</" << name << ">" << endl;
            return oss.str();
        }
    };
    struct HtmlBuilder
    {
        HtmlBuilder(string root_name)
        {
            root.name = root_name;
        }
        HtmlBuilder& add_child(string child_name, string child_text){
            HtmlElement e(child_name, child_text);
            root.elements.emplace_back(e);
            return *this;
        }
        HtmlElement root;

        operator HtmlElement() { return root; }
        string str() const
        {
            return root.str();
        }
    };


};
static builder::HtmlBuilder build(string root_name){
    return builder::HtmlBuilder(root_name);
}

#endif // BUILDER_H
