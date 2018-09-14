#!/bin/sh

date=`date +%Y-%m-%d`
datetime=`date "+%Y-%m-%d %H:%M:%S"`

read -p "   Module name: " title
read -p "   Developer name: " author

title_=$(echo $title | sed -e 's/ /_/g')
filetitle=$title_.py

touch imx/developing/$filetitle

echo '"""**' $title ' Module**' 						>> imx/developing/$filetitle
echo ' ' 									>> imx/developing/$filetitle
echo 'Module description' 							>> imx/developing/$filetitle
echo ''										>> imx/developing/$filetitle
echo ':platform: ...' 								>> imx/developing/$filetitle
echo ':synopsis: This module ...' 						>> imx/developing/$filetitle
echo ' ' 									>> imx/developing/$filetitle
echo '.. moduleauthor:: your_name <your_corporate_email>' 			>> imx/developing/$filetitle
echo '   .. note:: ' $date ' [your_nick]  first version released' 		>> imx/developing/$filetitle
echo ' ' 									>> imx/developing/$filetitle
echo '"""' 									>> imx/developing/$filetitle
echo 'import sys' 								>> imx/developing/$filetitle
echo ' ' 									>> imx/developing/$filetitle
echo 'def who():' 								>> imx/developing/$filetitle
echo '  """' 									>> imx/developing/$filetitle
echo '  Print developer name.' 							>> imx/developing/$filetitle
echo '  """' 									>> imx/developing/$filetitle
echo '  who = "' $author '"' 							>> imx/developing/$filetitle
echo '  print("Written by:%s" % str(who))' 					>> imx/developing/$filetitle

echo
echo 'Python' $filetitle 'file was created with success on imx/developing/ folder.' 
