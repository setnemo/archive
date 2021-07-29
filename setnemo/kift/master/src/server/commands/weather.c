/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weather.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 22:22:13 by vrybalko          #+#    #+#             */
/*   Updated: 2018/09/04 21:14:44 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "external/cJSON.h"
#include "server/config.h"
#include "weather_private.h"

static size_t		write_memory_callback(void *contents, size_t size,
						size_t nmemb, void *userp)
{
	size_t			realsize;
	t_memory_chunk	*mem;

	mem = (t_memory_chunk*)userp;
	realsize = size * nmemb;
	mem->memory = realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory == NULL)
		return (0);
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
	return (realsize);
}

static char			*get_weather_data(void *arg)
{
	t_curl			*curl;
	t_memory_chunk	chunk;

	(void)arg;
	chunk.memory = malloc(1);
	chunk.size = 0;
	curl_global_init(CURL_GLOBAL_ALL);
	if (!(curl = curl_easy_init()))
	{
		free(chunk.memory);
		return (NULL);
	}
	curl_easy_setopt(curl, CURLOPT_URL, "https://api.darksky.net/forecast/"\
			WEATHER_API_KEY"/"WEATHER_GEO_LOCATION"?units=si");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	if (curl_easy_perform(curl) != CURLE_OK)
	{
		free(chunk.memory);
		chunk.memory = NULL;
	}
	curl_easy_cleanup(curl);
	curl_global_cleanup();
	return (chunk.memory);
}

static char			*parse_daily_summary(char *data)
{
	cJSON			*forecast;
	const cJSON		*daily;
	const cJSON		*summary;
	char			*res;

	if (!(forecast = cJSON_Parse(data)))
		return (NULL);
	daily = cJSON_GetObjectItemCaseSensitive(forecast, "daily");
	if (!daily)
	{
		cJSON_Delete(forecast);
		return (NULL);
	}
	summary = cJSON_GetObjectItemCaseSensitive(daily, "summary");
	if (!summary || !cJSON_IsString(summary) || !summary->valuestring)
	{
		cJSON_Delete(forecast);
		return (NULL);
	}
	res = strdup(summary->valuestring);
	cJSON_Delete(forecast);
	return (res);
}

char				*weather_callback(void *arg)
{
	char		*data;

	data = get_weather_data(arg);
	if (!data)
		return (strdup("Failed to get weather forecast"));
	else if (strncmp(data, "Forbid", 6) == 0)
		return (strdup("Your API key is invalid"));
	return (parse_daily_summary(data));
}
