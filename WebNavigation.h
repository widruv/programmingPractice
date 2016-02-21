#ifndef _WEB_NAVIGATION_H
#define _WEB_NAVIGATION_H

#include <string>
#include <stack>

class WebNavigation
{
public:
	WebNavigation();
	~WebNavigation(){}

	int execute( std::string command, std::string& currentPage );

protected:
	std::string back();
	std::string forward();
	std::string visit( const std::string webSite );
	bool quit();

private:
	enum excuteResult{ QUIT = 0, EXECUTE, IGNORED };
	enum parsingResult { FAIL = 0, SUCCESS };

	void clearForwardStack();
	int getWebSiteFromCommand( const std::string& command, std::string& webSite );

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
