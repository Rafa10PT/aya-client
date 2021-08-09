#include <iostream>
#include <cstring>
#include <cstdlib>
#include <getopt.h>

#include "aya/context.hpp"

static aya::context ctx;

static constexpr int arg_max = 7;

void help() {
	std::cout <<
		"Usage: aya-client <options...>\n"
		"[-m, --mode]	<mode>	Specify the connection mode.\n"
		"Available modes:\n"
		"usb:	For USB connection.\n"
		"wlan:	For WLAN connection, which requires setting an IP and port with the -i option.\n\n"
		"[-i, --ip] <ipv4>:<port>	Specifies the IP address of the server.\n"
		"<ipv4>:	X.X.X.X where X is decimal for each byte.\n"
		"<port>:	Y where Y is a valid decimal port halfword.\n\n\n"
		"Media options (required at least one):\n"
		"--with-video		In order to stream input video from the connected device.\n"
		"--with-audio		In order to stream input audio from the connected device.\n";
	exit(-1);
}


int main(int argc, char *argv[]) {
	if(argc == 1 || argc > arg_max) help();

	bool ip_set = false;
	while(true) {
		static const struct option options[] = {
			{"mode", 1, nullptr, 'm'},
			{"ip", 1, nullptr, 'i'},
			{"with-video", 0, nullptr, 0},
			{"with-audio", 0, nullptr, 1},
			{nullptr, 0, nullptr, 0}
		};
		int op_idx;
		int op = getopt_long(argc, argv, "m:i:", options, &op_idx);

		if(op == -1) break;

		switch(op) {
			case 'm': {
				if(!std::strcmp(optarg, "usb"))
					ctx.set_usb();

				else if(!std::strcmp(optarg, "wlan"))
					ctx.set_wlan();
				
				else help();

				break;
			}

			case 'i': {
				if(!ctx.try_set_ip(optarg))
					help();
				ip_set = true;
				break;
			}

			case 0:
				ctx.set_video();
				break;
			case 1:
				ctx.set_audio();
				break;

			default:
				help();
				return -1;
		}
	}

	if((ctx.is_wlan() && !ip_set) || !ctx.has_mode() || !ctx.has_media()) help();

	ctx.run();

	return 0;
}

