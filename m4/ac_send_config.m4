
AC_DEFUN([AC_SEND_CONFIG],[

if false; then

rm -f __target_id
echo "Subject: blitz machineinfo" >>__target_id
echo "" >>__target_id
echo "Target: " $target >>__target_id
echo "Compiler: " $bz_compiler >>__target_id
echo "Date: " `date` >>__target_id

echo " "
echo "****************"
echo "With your permission, this script will send a mail message"
echo "containing some information about your hardware, OS, and compiler."
echo "This message will be sent via an anonymous remailer, so all"
echo "identifying information about you and your organization will be"
echo "removed.  These mail messages allow the Blitz++ developers to"
echo "gauge how large the user base is, and what platforms are being"
echo "used.  The email message will look like this:"
echo " "
echo "TO: anonymous remailer"
cat __target_id

echo " "
echo "Is it okay if this message is sent? (yes/no)"
read cansendtarget

case "$cansendtarget" in
  y*)
     sendmail tveldhui@seurat.uwaterloo.ca <__target_id
     echo "Thanks.  The mail has been sent."
     touch .bz_surveyed
  ;;
  *)
     echo "No mail was sent."
  ;;
esac

rm -f __target_id

fi

])
