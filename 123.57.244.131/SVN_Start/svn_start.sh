#!/bin/bash

killall svnserver
svnserve -d -r /svn/repos/kun
