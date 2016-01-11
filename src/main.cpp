#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include <yaml-cpp/yaml.h>

#include "config.h"

#define ERR_FILE_NOT_FOUND (-1)

std::vector<std::string> parse (std::string const& query)
{
    std::vector<std::string> result;

    size_t start=0, end=query.find(".");
    
    for (;end != std::string::npos; end = query.find(".", start)) {
        result.push_back(query.substr(start, end-start));

        start = end + 1;
    }
    
    result.push_back(query.substr(start, end));
    
    return result;
}

void usage (int argc, char **argv)
{
    std::cout
    << "yml v"
    << YML_VERSION_MAJOR << "."
    << YML_VERSION_MINOR << "."
    << YML_VERSION_PATCH
    << std::endl
    << "Usage: "
    << argv[0]
    << " file query"
    << std::endl
    ;
}

const YAML::Node search (YAML::Node node, std::string query)
{
    std::vector<std::string> lookup = parse (query);
    
    for (auto query: lookup) {
        node = node[query];
        
        if (!node.IsDefined()) {
            throw new std::logic_error(std::string("undefined query: ") + query);
        }
    }
    
    return node;
}

int main (int argc, char **argv)
{
    if (argc != 3) {
        usage (argc, argv);
        
        return EXIT_FAILURE;
    }
    
    YAML::Node node;
    
    try {
        node = YAML::LoadFile(argv[1]);
    } catch (YAML::BadFile e) {
        std::cerr << "ERROR: YAML::BadFile: " << e.what() << std::endl;
        
        return ERR_FILE_NOT_FOUND;
    }
    
    std::string query (argv[2]);
    
    YAML::Node result = search (node, query);
    
#ifdef DEBUG
    std::cerr
    << "query: "    << query
    << " [defined:" << result.IsDefined()
    << ",null:"     << result.IsNull()
    << ",scalar:"   << result.IsScalar()
    << ",sequence:" << result.IsSequence()
    << ",map:"      << result.IsMap()
    << "]" << std::endl
    ;
#endif
    
    std::cout << result << std::endl;
    
    return EXIT_SUCCESS;
}