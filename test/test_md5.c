/*!
 * @file test_md5.c
 *
 * @section LICENSE
 *
 * Copyright &copy; 2016, Scott K Logan
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * * Neither the name of OpenELP nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * EchoLink&reg; is a registered trademark of Synergenics, LLC
 *
 * @author Scott K Logan <logans@cottsay.net>
 */

#include "digest.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	const char md5_challenge[] = "thequickbrownfox";
	const uint8_t md5_control[16] = { 0x30, 0x8f, 0xb7, 0x6d, 0xc4, 0xd7, 0x30, 0x36, 0x0e, 0xe3, 0x39, 0x32, 0xd2, 0xfb, 0x10, 0x56 };
	const char md5_control_str[33] = "308fb76dc4d730360ee33932d2fb1056";
	uint8_t md5_result[16] = { 0x00 };
	char md5_result_str[33] = "";
	int ret = 0;

	digest_get((uint8_t *)md5_challenge, strlen(md5_challenge), md5_result);

	ret = digest_to_str(md5_control, md5_result_str);
	if (ret != 0)
	{
		fprintf(stderr, "Error: digest_to_str returned %d\n", ret);
		return ret;
	}

	if (strcmp(md5_control_str, md5_result_str) != 0)
	{
		fprintf(stderr, "Error: digest_to_str mismatch. Expected 0x%s Got: 0x%s\n", md5_control_str, md5_result_str);
		return -EINVAL;
	}

	ret = digest_to_str(md5_result, md5_result_str);
	if (ret != 0)
	{
		fprintf(stderr, "Error: digest_to_str returned %d\n", ret);
		return ret;
	}

	if (strcmp(md5_control_str, md5_result_str) != 0)
	{
		fprintf(stderr, "Error: digest_get mismatch. Expected: 0x%s Got: 0x%s\n", md5_control_str, md5_result_str);
		return -EINVAL;
	}

	return 0;
}
