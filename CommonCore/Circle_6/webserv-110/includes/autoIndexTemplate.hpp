/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  autoIndexTemplate.hpp                                  ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/03/20 10:13:52 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/03/20 10:13:55 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#pragma once
#include <string>

static const std::string AUTOINDEX_TEMPLATE =
"<!DOCTYPE html>\n"
"<html lang=\"en\">\n"
"<head>\n"
"<meta charset=\"UTF-8\">\n"
"<title>Index of {{PATH}}</title>\n"
"<style>\n"
"body {"
"  font-family: Arial, sans-serif;"
"  background: linear-gradient(135deg, rgb(0,255,255), rgb(255,0,255));"
"  display: flex; justify-content: center; align-items: center;"
"  height: 100vh; margin: 0;"
"}\n"
".box {"
"  background: white;"
"  padding: 30px;"
"  border-radius: 16px;"
"  width: 600px;"
"  max-height: 80vh;"
"  overflow-y: auto;"
"  box-shadow: 0 4px 12px rgba(0,0,0,0.3);"
"}\n"
"ul { list-style: none; padding: 0; }\n"
"li { margin: 10px 0; }\n"
"a { text-decoration: none; color: #333; font-weight: bold; }\n"
"a:hover { color: #942f62; }\n"
".dir { color: #0077cc; }\n"
"</style>\n"
"</head>\n"
"<body>\n"
"<div class=\"box\">\n"
"<h1>Index of {{PATH}}</h1>\n"
"<ul>\n"
"{{FILES}}\n"
"</ul>\n"
"</div>\n"
"</body>\n"
"</html>\n";
