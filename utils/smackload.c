/*
 * This file is part of libsmack
 *
 * Copyright (C) 2011 Intel Corporation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 * Authors:
 * Brian McGillion <brian.mcgillion@intel.com>
 */

#include "common.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int usage(const char *bin)
{
	fprintf(stderr, "Usage: %s [-c] <path>\n", bin);
	exit(1);
}

int main(int argc, char **argv)
{
	int clear = 0;
	int c;

	while ((c = getopt(argc, argv, "c")) != -1) {
		switch (c) {
			case 'c':
				clear = 1;
				break;
			default:
				usage(argv[0]);
		}
	}

	if (optind == argc)
		usage(argv[0]);

	if (is_smackfs_mounted() != 1) {
		fprintf(stderr, "ERROR: SmackFS is not mounted.\n");
		return -1;
	}

	if (apply_rules(argv[optind], clear))
		perror("Applying rules");

	exit(0);
}
