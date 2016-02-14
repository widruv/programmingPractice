#ifndef _WEB_NAVIGATION_H
#define _WEB_NAVIGATION_H

#include <string>
#include <stack>

class WebNavigation
{
public:
	WebNavigation();
	~WebNavigation(){}

	bool excute( std::string command, std::string& currentPage );

protected:
	std::string back();
	std::string forward();
	std::string visit( const std::string webSite );
	bool quit();

private:
	enum EXCUTE_RESULT{ QUIT = 0, SUCCESS, IGNORED };

	void clearForwardStack();
	int getWebSiteStartPosition( char* afterVisitCommand );

	std::stack<std::string> _forwardStack;
	std::stack<std::string> _backwardStack;

	const char* _initialPage;
	const char* _failMsg;

	const char* _backCommand;
	const char* _forwardCommand;
	const char* _visitCommand;
	const char* _quitCommand;

	std::string _currentPage;
};

#endif
