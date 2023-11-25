Action()
{

/*Correlation comment - Do not change!  Original value='ffeeb7489d5a44f8a027c08548542242' Name ='act_token' Type ='ResponseBased'*/
	
	lr_start_transaction("Login");

	web_reg_save_param_regexp(
		"ParamName=act_token",
		"RegExp=act=(.*?);",
		SEARCH_FILTERS,
		"Scope=Cookies",
		"IgnoreRedirections=No",
		LAST);

	web_url("login", 
		"URL=https://account.mail.ru/login", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t2044.inf", 
		"Mode=HTTP", 
		LAST);

	
	web_reg_find("Search=All",
		"Text=location: https://e.mail.ru/messages/inbox",
		LAST);

	web_submit_data("auth",
		"Action=https://auth.mail.ru/cgi-bin/auth",
		"Method=POST",
		"EncodeAtSign=YES",
		"RecContentType=text/html",
		"Referer=https://account.mail.ru/",
		"Snapshot=t2162.inf",
		"Mode=HTTP",
		ITEMDATA,
		"Name=username", "Value={login}", ENDITEM,
		"Name=Login", "Value={login}", ENDITEM,
		"Name=password", "Value={pwd}", ENDITEM,
		"Name=Password", "Value={pwd}", ENDITEM,
		"Name=saveauth", "Value=1", ENDITEM,
		"Name=new_auth_form", "Value=1", ENDITEM,
		"Name=FromAccount", "Value=opener=account&twoSteps=1", ENDITEM,
		"Name=act_token", "Value={act_token}", ENDITEM,
		"Name=page", "Value=https://e.mail.ru/messages/inbox?authid=lp4305ek.52&back=1&dwhsplit=s10273.b1ss12743s&from=login&x-login-auth=1", ENDITEM,
		"Name=back", "Value=1", ENDITEM,
		"Name=lang", "Value=ru_RU", ENDITEM,
		LAST);
	
	web_reg_save_param_json(
		"ParamName=token",
		"QueryString=$.body.token",
		LAST);
	
	web_submit_data("short",
		"Action=https://e.mail.ru/api/v1/user/short",
		"Method=POST",
		"EncodeAtSign=YES",
		"TargetFrame=",
		"RecContentType=application/json",
		"Referer=https://e.mail.ru/inbox",
		"Snapshot=t183.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=email", "Value={login}", ENDITEM,
		"Name=htmlencoded", "Value=false", ENDITEM,
		"Name=token", "Value=", ENDITEM,
		LAST);
		
	lr_end_transaction("Login",LR_AUTO);

	lr_start_transaction("New_folder");

	
	web_reg_find("Search=Body",
		"Text=\"status\":200",
		LAST);

	web_submit_data("add", 
		"Action=https://e.mail.ru/api/v1/folders/add", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=https://e.mail.ru/inbox/?authid=lp4305ek.52&back=1%2C1&dwhsplit=s10273.b1ss12743s&from=login&x-login-auth=1", 
		"Snapshot=t2315.inf", 
		"Mode=HTTP", 
		"EncodeAtSign=YES", 
		ITEMDATA, 
		"Name=folders", "Value=[{\"name\":\"{random}\",\"id\":null,\"system\":false,\"type\":\"\",\"parent\":-1,\"open\":true,\"security\":false,\"messages_total\":0,\"messages_unread\":0,\"child\":false,\"children\":false,\"archive\":false,\"collapse\":false,\"only_web\":false}]", ENDITEM, 
		"Name=email", "Value={login}", ENDITEM, 
		"Name=htmlencoded", "Value=false", ENDITEM, 
		"Name=token", "Value={token}", ENDITEM, 
		LAST);


	lr_end_transaction("New_folder",LR_AUTO);

	

	lr_start_transaction("exit");
	
	
	web_reg_find("Search=All",
		"Text=Location: https://mail.ru/?from=logout",
		LAST);

	web_url("logout", 
		"URL=https://auth.mail.ru/cgi-bin/logout?next=1&lang=ru_RU&page=https%3A%2F%2Fmail.ru%2F%3Ffrom%3Dlogout", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://e.mail.ru/", 
		"Snapshot=t2342.inf", 
		"Mode=HTTP", 
		LAST);


	lr_end_transaction("exit",LR_AUTO);

	return 0;
}