#include "../pch.h"

#include "../../../../labs/lab6/http_url/headers/HttpUrl/CHttpUrl.h"

TEST_CASE("HttpUrl constructed with string. Url is not correct")
{
	WHEN("Url is empty")
	{
		REQUIRE_THROWS_AS(HttpUrl(""), UrlParsingError);
	}
	WHEN("Protocol spelled incorrectly")
	{
		REQUIRE_THROWS_AS(HttpUrl("htasdtp://www.mysite.com/docs/document1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Missed ':' after protocol")
	{
		REQUIRE_THROWS_AS(HttpUrl("http//www.mysite.com/docs/document1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Missed '/' after protocol")
	{
		REQUIRE_THROWS_AS(HttpUrl("http:/www.mysite.com/docs/document1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Missed all '/' after protocol")
	{
		REQUIRE_THROWS_AS(HttpUrl("http:www.mysite.com/docs/document1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Missed '/' after domain")
	{
		REQUIRE_THROWS_AS(HttpUrl("http://www.mysite.comdocsdocument1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Missed '.' in domain")
	{
		REQUIRE_THROWS_AS(HttpUrl("http://wwwmysitecom/docs/document1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Too much '.' in domain #1")
	{
		REQUIRE_THROWS_AS(HttpUrl("http://www..mysite.com/doc/sdocument1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Too much '.' in domain #2")
	{
		REQUIRE_THROWS_AS(HttpUrl("http://www.mysite..com/doc/sdocument1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Too much '.' in domain #3")
	{
		REQUIRE_THROWS_AS(HttpUrl("http://www..mysite..com/doc/sdocument1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Protocol typed twice")
	{
		REQUIRE_THROWS_AS(HttpUrl("http::http://www.mysite.com/doc/sdocument1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Missed port, but ':' after domain exists")
	{
		REQUIRE_THROWS_AS(HttpUrl("http://www.mysite.com:/doc/sdocument1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Wrong sequence #1")
	{
		REQUIRE_THROWS_AS(HttpUrl("sadasd.asdsad.asdasd//:sadasd.asdsad.asdasd"), UrlParsingError);
	}
	WHEN("Wrong sequence #2")
	{
		REQUIRE_THROWS_AS(HttpUrl("document1.html?page=30&lang=en#title/docs/www.mysite.com//:http"), UrlParsingError);
	}
	WHEN("Wrong sequence #3")
	{
		REQUIRE_THROWS_AS(HttpUrl("document1.html?page=30&lang=en#title//docs//www.mysite.com///:http"), UrlParsingError);
	}
}
