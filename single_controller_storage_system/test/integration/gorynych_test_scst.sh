#!/bin/bash
DST_BIN_DIR="/tmp/open-close-test"
TARGET_NAME='qn.2017-03.iscsi.lan:tgt-super-test-iscsi'
TEST_DEVICE="/disk5"
TEST_DEVICE_FORMATTED="_disk5"

function close_all
{
    printf "done\nExcluding iSCSI LUNs from the system...\n"
    iscsiadm -m node -u
    printf "done\nStopping gorynych-control...\n"
    ssh -i /var/lib/jenkins/.ssh/id_rsa root@193.169.52.184 killall gorynych-control
    printf "done\nRestarting scst...\n"
    ssh -i /var/lib/jenkins/.ssh/id_rsa root@193.169.52.184 systemctl restart scst
}

printf "done\nRestarting scst...\n"
ssh -i /var/lib/jenkins/.ssh/id_rsa root@193.169.52.184 systemctl restart scst

close_all

printf "starting gorynych-control...\n"
bash -c "ssh -i /var/lib/jenkins/.ssh/id_rsa root@193.169.52.184 ${DST_BIN_DIR}/gorynych-control&"  &> /dev/null

printf "done\nExporting ${TEST_DEVICE} file in ${TARGET_NAME} target as LUN0...\n"
echo "open ${TEST_DEVICE} ${TARGET_NAME} 0" | ssh -i /var/lib/jenkins/.ssh/id_rsa root@193.169.52.184 ${DST_BIN_DIR}/gorynych-admin

printf "done\nImporting target on our machine and getting target list...\n"
TARGETS_OUTPUT=$(iscsiadm -m discovery -t st -p 193.169.52.184 | grep ${TARGET_NAME})
if [[ $TARGETS_OUTPUT =~ .*${TARGET_NAME}.* ]]
then
   echo "Target there!"
else
   echo "Target not found!"
   close_all
   exit 1
fi
printf "done\nImporting LUNs...\n"
iscsiadm -m node --login

printf "done\nChecking disk list in our system...\n"
LSSCSI_OUTPUT=$(lsscsi | grep ${TEST_DEVICE_FORMATTED})
if [[ $LSSCSI_OUTPUT =~ .*${TEST_DEVICE_FORMATTED}.* ]]
then
   echo "LUN there!"
else
   echo "LUN not found!"
   close_all
   exit 1
fi

printf "done\nExcluding iSCSI LUNs from the system...\n"
iscsiadm -m node -u

printf "\ndone\nChecking 'close' command...\n"
echo "close ${TEST_DEVICE} ${TARGET_NAME} 0" | ssh -i /var/lib/jenkins/.ssh/id_rsa root@193.169.52.184 ${DST_BIN_DIR}/gorynych-admin

printf "done\nImporting target on our machine and getting target list...\n"
TARGETS_OUTPUT=$(iscsiadm -m discovery -t st -p 193.169.52.184 | grep ${TARGET_NAME})
if [[ $TARGETS_OUTPUT =~ .*${TARGET_NAME}.* ]]
then
   echo "Target there, fail!"
   close_all
   exit 1
else
   echo "Target not found, success!"

fi
printf "done\nImporting LUNs...\n"
iscsiadm -m node --login

printf "done\nChecking disk list in our system...\n"
SCSTADMIN_OUTPUT=$(ssh -i /var/lib/jenkins/.ssh/id_rsa root@193.169.52.184 scstadmin -list_device | grep ${TEST_DEVICE_FORMATTED})
if [[ $SCSTADMIN_OUTPUT =~ .*${TEST_DEVICE_FORMATTED}.* ]]
then
   echo "Disk in SCST, fail!"
   close_all
   exit 1
else
   echo "Disk not found in SCST, success!!"
fi

close_all

exit 0
