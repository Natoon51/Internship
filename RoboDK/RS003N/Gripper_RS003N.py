# This program allows moving gripper fingers
import sys # allows getting the passed argument parameters
from robodk import *

if len(sys.argv) < 2:
    print('Invalid parameters. This function must be called as MoveGripper(Gripper_Id, Distance)')
    print('Number of arguments: ' + str(len(sys.argv)))
    #raise Exception('Invalid parameters provided: ' + str(sys.argv))
    entry = mbox('Move gripper. Type:\n1 to open, 0 to close\n\nNote: this can be called as a program.\nExample: Gripper(1)', entry='0')
    if not entry:
        raise Exception('Operation cancelled by user')

    GRIPPER_VALUE = int(entry)*6

else:
    GRIPPER_VALUE = int(sys.argv[1])*6

from robolink import *    # API to communicate with RoboDK
RDK = Robolink()


finger_P = RDK.Item('FingerB')
finger_N = RDK.Item('FingerA')

if not finger_P.Valid() or not finger_N.Valid():
    raise Exception('Invalid Gripper ID')

finger_P.setPose(transl(0,+GRIPPER_VALUE,0))
finger_N.setPose(transl(0,-GRIPPER_VALUE,0))

# Set the station parameter
RDK.setParam('Gripper', GRIPPER_VALUE)





