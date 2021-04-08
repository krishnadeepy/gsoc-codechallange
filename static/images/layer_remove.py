import cv2
import glob
import numpy as np
for i in glob.glob("/home/kd/Desktop/GSOC_V3/static/images/sample_mask_files/*/*.jpeg"):
  mas=cv2.imread(i)
  mas=mas[:,:,2]
  mas=np.where(mas!=0,255,0)
  cv2.imwrite(i,mas)
