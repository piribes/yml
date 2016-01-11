#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>
#include <boost/spirit/include/phoenix.hpp>

// For Spirit Tesing
#include <boost/spirit/include/support_string_traits.hpp>

/*
 
 [0].powers[key].damage
 
 
 FORMAT EBNF
 
 query :== var ('.' query)
 var :== map | seq | scalar
 
 seq :== name? '[' pos ']'
 name :== <a string>
 pos :== <a number>
 
 scalar :== <a string>
 
 
 ## IMPLEMENT MAP LATER
 map :== name? '[' key ']'
 key :== <a string>
 
 */
//using boost::spirit::qi::rule;
//using boost::spirit::qi::lexeme;
////using boost::spirit::lit;
//using boost::spirit::ascii::string;
//using boost::spirit::ascii::digit;
//
////using boost::spirit::int_;
//using boost::spirit::qi::locals;
////using boost::spirit::_1;
//using boost::spirit::qi::_a;
//using boost::spirit::ascii::alpha;
//using boost::spirit::ascii::char_;
//using boost::spirit::ascii::space_type;

/*
 NOTE
 The first version will implement lookup of scalars ONLY.
 For example: scalar1.scalar2.scalar3
 */

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

//template<typename Iterator>
//struct grammar : qi::grammar<Iterator, std::vector<std::string>>
//{
//    grammar() : grammar::base_type(var)
//    {
//        var = ascii::string % '.';
//    }
//
//    qi::rule<Iterator, std::string> var;
//};

//
//std::vector<std::string> parse (std::string const& query)
//{
//    std::vector<std::string> result;
//    
//    // ATTEMPT #1
//    //    const char* const in = "one world";
//    //    std::cout << qi::parse(in[0], in[strlen(in)-1], ascii::string) << std::endl;                // works fine
//    ////    std::cout
//    ////    << qi::parse(in.begin(),
//    ////                 in.end(),
//    ////                 ascii::string >> ' ' >> ascii::string)
//    //    << std::endl;
//    
//    // ATTEMPT #2
//    //    std::string s("command:param1 param2");
//    //    std::string cmd, params;
//    //    qi::rule<char const*> xxx = +~qi::char_(':') >> ':' >> *qi::char_;
//    //    qi::parse(s.begin(), s.end(), xxx);
//    //
//    //    std::cout << "cmd: " << cmd << std::endl;
//    //    std::cout << "params: " << params << std::endl;
//    
//    // ATTEMPT #3
//    //rule<char const*> q;
//    
//    // Iniziamo con il parsing di scalar1.scalar2.scalar3(.scalarN)
//    //q %= string;// >> ( "." >> q );
//    
//    //    rule<char const*, std::vector<int>(), space_type> rs;
//    //    rs = int_;
//    //    std::vector<int> v;
//    //    //test_phrase_parser_attr("123 456 789", rs, v);
//    //    assert(v[0] ==  123);
//    //    assert(v[1] ==  456);
//    //    assert(v[2] ==  789);
//    
//    // ATTEMPT #4
//    //
//    //    qi::rule<std::string::const_iterator> rule =
//    ////    ascii::string >> ( qi::char_('.') >> ascii::string );
//    //    +~qi::char_(':') >> ':' >> *qi::char_;
//    //
//    //    qi::parse(query.cbegin(), query.cend(), rule);
//    //
//    //    return result;
//    
//    // ATTEMPT #5
//    auto start=0U;
//    
//    auto end=query.find(".");
//    
//    for (;
//         end != std::string::npos;
//         end = query.find(".", start))
//    {
//        result.push_back(query.substr(start, end-start));
//        
//        start = end + 1;
//    }
//    
//    result.push_back(query.substr(start, end));
//    
//    return result;
//}


template <typename P>
void test_parser(
                 char const* input, P const& p, bool full_match = true)
{
    using boost::spirit::qi::parse;
    
    char const* f(input);
    char const* l(f + strlen(f));
    if (parse(f, l, p) && (!full_match || (f == l)))
        std::cout << "ok" << std::endl;
    else
        std::cout << "fail" << std::endl;
}

template <typename P>
void test_phrase_parser(
                        char const* input, P const& p, bool full_match = true)
{
    using boost::spirit::qi::phrase_parse;
    using boost::spirit::ascii::space;
    
    char const* f(input);
    char const* l(f + strlen(f));
    if (phrase_parse(f, l, p, space) && (!full_match || (f == l)))
        std::cout << "ok" << std::endl;
    else
        std::cout << "fail" << std::endl;
}

template <typename P, typename T>
void test_parser_attr(
                      char const* input, P const& p, T& attr, bool full_match = true)
{
    using boost::spirit::qi::parse;
    
    char const* f(input);
    char const* l(f + strlen(f));
    if (parse(f, l, p, attr) && (!full_match || (f == l)))
        std::cout << "ok" << std::endl;
    else
        std::cout << "fail" << std::endl;
}

template <typename P, typename T>
void test_phrase_parser_attr(
                             char const* input, P const& p, T& attr, bool full_match = true)
{
    using boost::spirit::qi::phrase_parse;
    using boost::spirit::ascii::space;
    
    char const* f(input);
    char const* l(f + strlen(f));
    if (phrase_parse(f, l, p, space, attr) && (!full_match || (f == l)))
        std::cout << "ok" << std::endl;
    else
        std::cout << "fail" << std::endl;
}

struct printer
{
    typedef boost::spirit::utf8_string string;
    
    void element(string const& tag, string const& value, int depth) const
    {
        for (int i = 0; i < (depth*4); ++i) // indent to depth
            std::cout << ' ';
        
        std::cout << "tag: " << tag;
        if (value != "")
            std::cout << ", value: " << value;
        std::cout << std::endl;
    }
};

void print_info(boost::spirit::info const& what)
{
    using boost::spirit::basic_info_walker;
    
    printer pr;
    basic_info_walker<printer> walker(pr, what.tag, 0);
    boost::apply_visitor(walker, what.value);
}