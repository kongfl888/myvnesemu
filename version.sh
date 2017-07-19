#!/bin/sh


#update version info
cur_rev_num=`git rev-list HEAD | wc -l | awk '{print $1}'`
base_rev_num=`git rev-list 0.97 | wc -l | awk '{print $1}'`
((rev_num=$cur_rev_num-$base_rev_num))

#rev_sha1=`git rev-parse HEAD`
#rev_tag=`git describe --tag --abbrev=0`
#ver_major=`echo $rev_tag | awk -F$'.' '{print $1}'`
#ver_minor=`echo $rev_tag | awk -F$'.' '{print $2}'`
#ver_patch=`echo $rev_tag | awk -F$'.' '{print $3}'`

echo "#define Rversion \"$rev_num\"" > "./version_r.h"

exit
