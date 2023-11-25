#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lrs.h"

int getCurrentTimePlusValue(int value) {
    time_t currentTime;
    struct tm *timeInfo;
    int currentSeconds;
    int result;

    currentTime = time(NULL);
    timeInfo = localtime(&currentTime);
    currentSeconds = (timeInfo->tm_hour * 3600) + (timeInfo->tm_min * 60) + timeInfo->tm_sec;

    result = currentSeconds + value;

    return result;
}

Action()
{	
	int Y;
    int value;
    int result;

    Y = rand() % 100 + 1;
    value = Y;

    result = getCurrentTimePlusValue(value);

    lr_save_int(result, "current_time_plus_value");

	lr_start_transaction("01_openpage");

/*Correlation comment - Do not change!  Original value='3b393b404592426ba4f879195417b09f' Name ='act_token' Type ='ResponseBased'*/
	web_reg_save_param_regexp(
		"ParamName=act_token",
		"RegExp=act=(.*?);",
		LAST);

	web_reg_find("Search=Body",
		"Text=Mail.ru",
		LAST);

	web_url("mail.ru", 
		"URL=https://mail.ru/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t72.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("01_openpage",LR_AUTO);

	lr_start_transaction("02_login");

	web_reg_find("Search=All",
		"Text=location: https://e.mail.ru/messages/inbox",
		LAST);

	web_submit_data("auth",
		"Action=https://auth.mail.ru/cgi-bin/auth?from=navi",
		"Method=POST",
		"EncodeAtSign=YES",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=https://account.mail.ru/",
		"Snapshot=t151.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=username", "Value={login}", ENDITEM,
		"Name=Login", "Value={login}", ENDITEM,
		"Name=password", "Value={pwd}", ENDITEM,
		"Name=Password", "Value={pwd}", ENDITEM,
		"Name=saveauth", "Value=1", ENDITEM,
		"Name=new_auth_form", "Value=1", ENDITEM,
		"Name=FromAccount", "Value=opener=account&allow_external=1&twoSteps=1", ENDITEM,
		"Name=act_token", "Value={act_token}", ENDITEM,
		"Name=page", "Value=https://e.mail.ru/messages/inbox", ENDITEM,
		"Name=back", "Value=1", ENDITEM,
		"Name=lang", "Value=ru_RU", ENDITEM,
		LAST);

	lr_end_transaction("02_login",LR_AUTO);
	

	lr_start_transaction("03_send_mes");

/*Correlation comment - Do not change!  Original value='f423671ae61ae166ece781af624ffcdf:hdLwGvtjx2a6rFvntc5NEvzK8dH27teEyLOZajZoDOh7InRpbWUiOjE2OTQ2OTI2NTEsInR5cGUiOiJjc3JmIiwibm9uY2UiOiJlMDYzZThlYmVkNzdiMTRhIn0' Name ='token' Type ='Manual'*/
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
	
	web_reg_find("Search=Body",
		"Text=\"status\":200",
		LAST);

	web_submit_data("send",
		"Action=https://e.mail.ru/api/v1/k8s/messages/send",
		"Method=POST",
		"EncodeAtSign=YES",
		"TargetFrame=",
		"RecContentType=application/json",
		"Referer=https://e.mail.ru/inbox/",
		"Snapshot=t235.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=ATTACHMENTS_RESTORE", "Value=true", ENDITEM,
		"Name=ATTACHMENTS_EXPIRATION_TIME", "Value={ATTACHMENTS_EXPIRATION_TIME}", ENDITEM,
		"Name=id", "Value={id}", ENDITEM,
		"Name=source", "Value={\"draft\":\"\",\"reply\":\"\",\"forward\":\"\",\"schedule\":\"\"}", ENDITEM,
		"Name=headers", "Value={}", ENDITEM,
		"Name=template", "Value=0", ENDITEM,
		"Name=sign", "Value=0", ENDITEM,
		"Name=remind", "Value=0", ENDITEM,
		"Name=receipt", "Value=false", ENDITEM,
		"Name=subject", "Value={time}", ENDITEM,
		"Name=priority", "Value=3", ENDITEM,
		"Name=send_date", "Value=", ENDITEM,
		"Name=body", "Value={\"html\":\"<div>&nbsp;</div><div>What's up{random} {posled} {random_static}?   {current_time_plus_value}  {time}</div><div data-signature-widget=\\\"container\\\"><div data-signature-widget=\\\"content\\\"><div>--<br><br>Отправлено из Почты <a href=\\\"https://trk.mail.ru/c/zzm979\\\">Mail.ru</a></div></div></div>\",\"text\":\"\\n"
		"\\n"
		"Привет\\n"
		"Подпись\\n"
		"--\\n"
		"\\n"
		"Отправлено из Почты Mail.ru\"}", ENDITEM,
		"Name=from", "Value=<{login}>", ENDITEM,
		"Name=correspondents", "Value={\"to\":\"{send_mail_to_smn}\",\"cc\":\"\",\"bcc\":\"\"}", ENDITEM,
		"Name=folder_id", "Value=", ENDITEM,
		"Name=triggerModelChangePlease", "Value=true", ENDITEM,
		"Name=compose_stat", "Value={\"user_track\":\"m|311|300|1|1;m|200|119|1|0;m|202|41|1|0;m|203|16|1|0;k|2227|6;m|2847|76|1|1;m|204|124|1|1;c|169|0|512|232;m|37|6|1|0;m|203|51|1|1;m|203|20|1|0;m|202|32|1|1;m|202|35|1|1;c|176|0|419|206;m|26|6|1|0;m|403|4|1|1;k|974|6;k|56|1;k|174|6;m|1454|43|1|1;m|201|307|2|1;m|202|103|1|0;m|211|13|1|0;c|82|0|312|609\",\"build\":\"release-fmail-21810.1970-01-03T06_03_37\",\"serverTime\":1694518767253}", ENDITEM,
		"Name=delay_for_cancellation", "Value=true", ENDITEM,
		"Name=attaches", "Value={\"list\":[]}", ENDITEM,
		"Name=email", "Value={login}", ENDITEM,
		"Name=htmlencoded", "Value=false", ENDITEM,
		"Name=token", "Value={token}", ENDITEM,
		LAST);

	lr_end_transaction("03_send_mes",LR_AUTO);
	

	lr_start_transaction("04_logout");

	web_reg_find("Search=All",
		"Text=Location: https://mail.ru/?from=logout",
		LAST);

	web_url("logout", 
		"URL=https://auth.mail.ru/cgi-bin/logout?next=1&lang=ru_RU&page=https%3A%2F%2Fmail.ru%2F%3Ffrom%3Dlogout", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://e.mail.ru/", 
		"Snapshot=t249.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("04_logout",LR_AUTO);

	return 0;
}
