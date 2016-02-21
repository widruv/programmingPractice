#include "WebNavigation.h"

WebNavigation::WebNavigation()
{
	_initialPage = "http://www.acm.org/";
	_currentPage = _initialPage;
	_failMsg = "Ignored";

	_backCommand = "BACK";
	_forwardCommand = "FORWARD";
	_visitCommand = "VISIT";
	_quitCommand = "QUIT";
}

int WebNavigation::execute( std::string command,
		std::string& currentPage )
{
	currentPage = _failMsg;
	if( strcmp( command.c_str(), _quitCommand ) == 0 )
	{
		return quit();
	}

	if( strcmp( command.c_str(), _backCommand ) == 0 )
	{
		currentPage = back();
	}
	else if( strcmp( command.c_str(), _forwardCommand ) == 0 )
	{
		currentPage = forward();
	}
	else if( strncmp( command.c_str(), _visitCommand, strlen(_visitCommand) ) == 0 )
	{
		std::string webSite;
		currentPage = ( getWebSiteFromCommand( command, webSite ) == SUCCESS ?
				visit(webSite) : _failMsg );
	}

	if( strncmp( currentPage.c_str(), _failMsg, strlen(_failMsg) ) == 0 )
	{
		return IGNORED;
	}

	return EXECUTE;
}

int WebNavigation::getWebSiteFromCommand( const std::string& command, std::string& webSite )
{
	int visitCommandLength = strlen(_visitCommand);
	if( command[visitCommandLength] == '\0' || !isspace( command[visitCommandLength] ) )
	{
		return FAIL;
	}
	webSite.assign( &command[visitCommandLength+1] );

	return SUCCESS;
}

std::string WebNavigation::back()
{
	if( _backwardStack.empty() )
	{
		return _failMsg;
	}
	_forwardStack.push( _currentPage );
	_currentPage = _backwardStack.top();
	_backwardStack.pop();

	return _currentPage;
}

std::string WebNavigation::forward()
{
	if( _forwardStack.empty() )
	{
		return _failMsg;
	}

	_backwardStack.push( _currentPage );
	_currentPage = _forwardStack.top();
	_forwardStack.pop();

	return _currentPage;
}

std::string WebNavigation::visit( const std::string webSite )
{
	_backwardStack.push( _currentPage );
	_currentPage = webSite;

	clearForwardStack();

	return _currentPage;
}

bool WebNavigation::quit()
{
	return QUIT;
}

void WebNavigation::clearForwardStack()
{
	while( !_forwardStack.empty() )
	{
		_forwardStack.pop();
	}
}
