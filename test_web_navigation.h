#include <cxxtest/TestSuite.h>
#include <string>
#include "WebNavigation.h"

class TWebNavigation : public WebNavigation
{
public:
	std::string back()
	{
		return WebNavigation::back();
	}
	std::string forward()
	{
		return WebNavigation::forward();
	}
	std::string visit( const std::string webSite )
	{
		return WebNavigation::visit( webSite );
	}
	bool quit()
	{
		return WebNavigation::quit();
	}
};

const std::string initialPage = "http://www.acm.org/";
class WebNavigationTest : public CxxTest::TestSuite
{
public:
	enum EXCUTE_RESULT{ QUIT = 0, SUCCESS };

	void test_goBackEmptyBackwardStack(void)
	{
		TWebNavigation aWebNavigation;
		std::string currentPage = aWebNavigation.back();

		TS_ASSERT_EQUALS( currentPage, "Ignored" );
	}

	void test_goForwardEmptyForwardStack(void)
	{
		TWebNavigation aWebNavigation;
		std::string currentPage = aWebNavigation.forward();

		TS_ASSERT_EQUALS( currentPage, "Ignored" );
	}

	void test_visitWebSite(void)
	{
		TWebNavigation aWebNavigation;
		const std::string webSite( "http://acm.ashland.edu/" );
		std::string currentPage = aWebNavigation.visit( webSite );

		TS_ASSERT_EQUALS( currentPage, webSite );
	}

	void test_goBackAfterVisitWebSite(void)
	{
		TWebNavigation aWebNavigation;
		const std::string webSite( "http://acm.ashland.edu/" );
		std::string currentPage = aWebNavigation.visit( webSite );
		TS_ASSERT_EQUALS( currentPage, webSite );

		currentPage = aWebNavigation.back();
		TS_ASSERT_EQUALS( currentPage, initialPage );
	}

	void test_goForwardAfterBack(void)
	{
		TWebNavigation aWebNavigation;
		const std::string webSite( "http://acm.ashland.edu/" );

		std::string currentPage = aWebNavigation.visit( webSite );
		TS_ASSERT_EQUALS( currentPage, webSite );

		currentPage = aWebNavigation.back();
		TS_ASSERT_EQUALS( currentPage, initialPage );

		currentPage = aWebNavigation.forward();
		TS_ASSERT_EQUALS( currentPage, "http://acm.ashland.edu/" );
	}

	void test_goForwardAfterVisit(void)
	{
		TWebNavigation aWebNavigation;
		const std::string webSite( "http://acm.ashland.edu/" );
		std::string currentPage = aWebNavigation.visit( webSite );
		TS_ASSERT_EQUALS( currentPage, webSite );

		currentPage = aWebNavigation.forward();
		TS_ASSERT_EQUALS( currentPage, "Ignored" );
	}

	void test_excute(void)
	{
		TWebNavigation aWebNavigation;

		std::string currentPage;
		int ret = aWebNavigation.excute( "BACK", currentPage );
		TS_ASSERT_EQUALS( currentPage, "Ignored" );
		TS_ASSERT_EQUALS( ret, SUCCESS );

		ret = aWebNavigation.excute( "FORWARD", currentPage );
		TS_ASSERT_EQUALS( currentPage, "Ignored" );
		TS_ASSERT_EQUALS( ret, SUCCESS );

		ret = aWebNavigation.excute( "VISIT http://www.naver.com", currentPage );
		TS_ASSERT_EQUALS( currentPage, "http://www.naver.com" );
		TS_ASSERT_EQUALS( ret, SUCCESS );

		ret = aWebNavigation.excute( "QUIT", currentPage );
		TS_ASSERT_EQUALS( ret, QUIT );
	}

};
