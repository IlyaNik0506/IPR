Action()
{
    int i;
    web_reg_save_param_regexp(
        "ParamName=country_name",
        "RegExp=<h3 class=\"country-name\">\\s*<i class=\"flag-icon flag-icon-[a-z]+\"></i>\\s*([^<]+)",
        "Ordinal=ALL",
        LAST
    );

    web_reg_save_param_regexp(
        "ParamName=capital",
        "RegExp=<strong>Capital:</strong> <span class=\"country-capital\">([^<]+)",
        "Ordinal=ALL",
        LAST
    );

    web_reg_save_param_regexp(
        "ParamName=population",
        "RegExp=<strong>Population:</strong> <span class=\"country-population\">([^<]+)",
        "Ordinal=ALL",
        LAST
    );

    web_reg_save_param_regexp(
        "ParamName=area",
        "RegExp=<strong>Area \\(km<sup>2</sup>\\):</strong> <span class=\"country-area\">([^<]+)",
        "Ordinal=ALL",
        LAST
    );

    web_url("GetPage",
        "URL=https://www.scrapethissite.com/pages/simple/",
        "Resource=0",
        "RecContentType=text/html",
        "Referer=",
        "Snapshot=t1.inf",
        "Mode=HTML",
        LAST
    );


    for (i = 1; i <= atoi(lr_eval_string("{country_name_count}")); i++) {
        lr_save_string(lr_eval_string(lr_paramarr_idx("country_name", i)), "Param_country_name");
        lr_save_string(lr_eval_string(lr_paramarr_idx("capital", i)), "Param_capital");
        lr_save_string(lr_eval_string(lr_paramarr_idx("population", i)), "Param_population");
        lr_save_string(lr_eval_string(lr_paramarr_idx("area", i)), "Param_area");

        lr_output_message("Страна: %s, Столица: %s, Население: %s человек, Площадь: %s км2",
            lr_eval_string("{Param_country_name}"),
            lr_eval_string("{Param_capital}"),
            lr_eval_string("{Param_population}"),
            lr_eval_string("{Param_area}")
        );
    }

    return 0;
}
