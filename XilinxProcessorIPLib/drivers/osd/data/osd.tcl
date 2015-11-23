##############################################################################
#
# Copyright (C) 2008 - 2014 Xilinx, Inc.  All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"),to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# Use of the Software is limited solely to applications:
# (a) running on a Xilinx device, or
# (b) that interact with a Xilinx device through a bus or interconnect.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
# OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# Except as contained in this notice, the name of the Xilinx shall not be used
# in advertising or otherwise to promote the sale, use or other dealings in
# this Software without prior written authorization from Xilinx.
###############################################################################
#uses "xillib.tcl"

proc generate {drv_handle} {
    ::hsi::utils::define_include_file $drv_handle "xparameters.h" "XOSD" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" "C_NUM_LAYERS" "C_S_AXIS_VIDEO_DATA_WIDTH" "C_LAYER0_TYPE" "C_LAYER1_TYPE" "C_LAYER2_TYPE" "C_LAYER3_TYPE" "C_LAYER4_TYPE" "C_LAYER5_TYPE" "C_LAYER6_TYPE" "C_LAYER7_TYPE" "C_LAYER0_IMEM_SIZE" "C_LAYER0_INS_BOX_EN" "C_LAYER0_INS_LINE_EN" "C_LAYER0_INS_TEXT_EN" "C_LAYER0_CLUT_SIZE" "C_LAYER0_CLUT_MEMTYPE" "C_LAYER0_FONT_NUM_CHARS" "C_LAYER0_FONT_WIDTH" "C_LAYER0_FONT_HEIGHT" "C_LAYER0_FONT_BPP" "C_LAYER0_FONT_ASCII_OFFSET" "C_LAYER0_TEXT_NUM_STRINGS" "C_LAYER0_TEXT_MAX_STRING_LENGTH" "C_LAYER1_IMEM_SIZE" "C_LAYER1_INS_BOX_EN" "C_LAYER1_INS_LINE_EN" "C_LAYER1_INS_TEXT_EN" "C_LAYER1_CLUT_SIZE" "C_LAYER1_CLUT_MEMTYPE" "C_LAYER1_FONT_NUM_CHARS" "C_LAYER1_FONT_WIDTH" "C_LAYER1_FONT_HEIGHT" "C_LAYER1_FONT_BPP" "C_LAYER1_FONT_ASCII_OFFSET" "C_LAYER1_TEXT_NUM_STRINGS" "C_LAYER1_TEXT_MAX_STRING_LENGTH" "C_LAYER2_IMEM_SIZE" "C_LAYER2_INS_BOX_EN" "C_LAYER2_INS_LINE_EN" "C_LAYER2_INS_TEXT_EN" "C_LAYER2_CLUT_SIZE" "C_LAYER2_CLUT_MEMTYPE" "C_LAYER2_FONT_NUM_CHARS" "C_LAYER2_FONT_WIDTH" "C_LAYER2_FONT_HEIGHT" "C_LAYER2_FONT_BPP" "C_LAYER2_FONT_ASCII_OFFSET" "C_LAYER2_TEXT_NUM_STRINGS" "C_LAYER2_TEXT_MAX_STRING_LENGTH" "C_LAYER3_IMEM_SIZE" "C_LAYER3_INS_BOX_EN" "C_LAYER3_INS_LINE_EN" "C_LAYER3_INS_TEXT_EN" "C_LAYER3_CLUT_SIZE" "C_LAYER3_CLUT_MEMTYPE" "C_LAYER3_FONT_NUM_CHARS" "C_LAYER3_FONT_WIDTH" "C_LAYER3_FONT_HEIGHT" "C_LAYER3_FONT_BPP" "C_LAYER3_FONT_ASCII_OFFSET" "C_LAYER3_TEXT_NUM_STRINGS" "C_LAYER3_TEXT_MAX_STRING_LENGTH" "C_LAYER4_IMEM_SIZE" "C_LAYER4_INS_BOX_EN" "C_LAYER4_INS_LINE_EN" "C_LAYER4_INS_TEXT_EN" "C_LAYER4_CLUT_SIZE" "C_LAYER4_CLUT_MEMTYPE" "C_LAYER4_FONT_NUM_CHARS" "C_LAYER4_FONT_WIDTH" "C_LAYER4_FONT_HEIGHT" "C_LAYER4_FONT_BPP" "C_LAYER4_FONT_ASCII_OFFSET" "C_LAYER4_TEXT_NUM_STRINGS" "C_LAYER4_TEXT_MAX_STRING_LENGTH" "C_LAYER5_IMEM_SIZE" "C_LAYER5_INS_BOX_EN" "C_LAYER5_INS_LINE_EN" "C_LAYER5_INS_TEXT_EN" "C_LAYER5_CLUT_SIZE" "C_LAYER5_CLUT_MEMTYPE" "C_LAYER5_FONT_NUM_CHARS" "C_LAYER5_FONT_WIDTH" "C_LAYER5_FONT_HEIGHT" "C_LAYER5_FONT_BPP" "C_LAYER5_FONT_ASCII_OFFSET" "C_LAYER5_TEXT_NUM_STRINGS" "C_LAYER5_TEXT_MAX_STRING_LENGTH" "C_LAYER6_IMEM_SIZE" "C_LAYER6_INS_BOX_EN" "C_LAYER6_INS_LINE_EN" "C_LAYER6_INS_TEXT_EN" "C_LAYER6_CLUT_SIZE" "C_LAYER6_CLUT_MEMTYPE" "C_LAYER6_FONT_NUM_CHARS" "C_LAYER6_FONT_WIDTH" "C_LAYER6_FONT_HEIGHT" "C_LAYER6_FONT_BPP" "C_LAYER6_FONT_ASCII_OFFSET" "C_LAYER6_TEXT_NUM_STRINGS" "C_LAYER6_TEXT_MAX_STRING_LENGTH" "C_LAYER7_IMEM_SIZE" "C_LAYER7_INS_BOX_EN" "C_LAYER7_INS_LINE_EN" "C_LAYER7_INS_TEXT_EN" "C_LAYER7_CLUT_SIZE" "C_LAYER7_CLUT_MEMTYPE" "C_LAYER7_FONT_NUM_CHARS" "C_LAYER7_FONT_WIDTH" "C_LAYER7_FONT_HEIGHT" "C_LAYER7_FONT_BPP" "C_LAYER7_FONT_ASCII_OFFSET" "C_LAYER7_TEXT_NUM_STRINGS" "C_LAYER7_TEXT_MAX_STRING_LENGTH"
    ::hsi::utils::define_config_file $drv_handle "xosd_g.c" "XOsd" "DEVICE_ID" "C_BASEADDR" "C_NUM_LAYERS" "C_S_AXIS_VIDEO_DATA_WIDTH" "C_LAYER0_TYPE" "C_LAYER1_TYPE" "C_LAYER2_TYPE" "C_LAYER3_TYPE" "C_LAYER4_TYPE" "C_LAYER5_TYPE" "C_LAYER6_TYPE" "C_LAYER7_TYPE" "C_LAYER0_IMEM_SIZE" "C_LAYER0_INS_BOX_EN" "C_LAYER0_INS_LINE_EN" "C_LAYER0_INS_TEXT_EN" "C_LAYER0_CLUT_SIZE" "C_LAYER0_CLUT_MEMTYPE" "C_LAYER0_FONT_NUM_CHARS" "C_LAYER0_FONT_WIDTH" "C_LAYER0_FONT_HEIGHT" "C_LAYER0_FONT_BPP" "C_LAYER0_FONT_ASCII_OFFSET" "C_LAYER0_TEXT_NUM_STRINGS" "C_LAYER0_TEXT_MAX_STRING_LENGTH" "C_LAYER1_IMEM_SIZE" "C_LAYER1_INS_BOX_EN" "C_LAYER1_INS_LINE_EN" "C_LAYER1_INS_TEXT_EN" "C_LAYER1_CLUT_SIZE" "C_LAYER1_CLUT_MEMTYPE" "C_LAYER1_FONT_NUM_CHARS" "C_LAYER1_FONT_WIDTH" "C_LAYER1_FONT_HEIGHT" "C_LAYER1_FONT_BPP" "C_LAYER1_FONT_ASCII_OFFSET" "C_LAYER1_TEXT_NUM_STRINGS" "C_LAYER1_TEXT_MAX_STRING_LENGTH" "C_LAYER2_IMEM_SIZE" "C_LAYER2_INS_BOX_EN" "C_LAYER2_INS_LINE_EN" "C_LAYER2_INS_TEXT_EN" "C_LAYER2_CLUT_SIZE" "C_LAYER2_CLUT_MEMTYPE" "C_LAYER2_FONT_NUM_CHARS" "C_LAYER2_FONT_WIDTH" "C_LAYER2_FONT_HEIGHT" "C_LAYER2_FONT_BPP" "C_LAYER2_FONT_ASCII_OFFSET" "C_LAYER2_TEXT_NUM_STRINGS" "C_LAYER2_TEXT_MAX_STRING_LENGTH" "C_LAYER3_IMEM_SIZE" "C_LAYER3_INS_BOX_EN" "C_LAYER3_INS_LINE_EN" "C_LAYER3_INS_TEXT_EN" "C_LAYER3_CLUT_SIZE" "C_LAYER3_CLUT_MEMTYPE" "C_LAYER3_FONT_NUM_CHARS" "C_LAYER3_FONT_WIDTH" "C_LAYER3_FONT_HEIGHT" "C_LAYER3_FONT_BPP" "C_LAYER3_FONT_ASCII_OFFSET" "C_LAYER3_TEXT_NUM_STRINGS" "C_LAYER3_TEXT_MAX_STRING_LENGTH" "C_LAYER4_IMEM_SIZE" "C_LAYER4_INS_BOX_EN" "C_LAYER4_INS_LINE_EN" "C_LAYER4_INS_TEXT_EN" "C_LAYER4_CLUT_SIZE" "C_LAYER4_CLUT_MEMTYPE" "C_LAYER4_FONT_NUM_CHARS" "C_LAYER4_FONT_WIDTH" "C_LAYER4_FONT_HEIGHT" "C_LAYER4_FONT_BPP" "C_LAYER4_FONT_ASCII_OFFSET" "C_LAYER4_TEXT_NUM_STRINGS" "C_LAYER4_TEXT_MAX_STRING_LENGTH" "C_LAYER5_IMEM_SIZE" "C_LAYER5_INS_BOX_EN" "C_LAYER5_INS_LINE_EN" "C_LAYER5_INS_TEXT_EN" "C_LAYER5_CLUT_SIZE" "C_LAYER5_CLUT_MEMTYPE" "C_LAYER5_FONT_NUM_CHARS" "C_LAYER5_FONT_WIDTH" "C_LAYER5_FONT_HEIGHT" "C_LAYER5_FONT_BPP" "C_LAYER5_FONT_ASCII_OFFSET" "C_LAYER5_TEXT_NUM_STRINGS" "C_LAYER5_TEXT_MAX_STRING_LENGTH" "C_LAYER6_IMEM_SIZE" "C_LAYER6_INS_BOX_EN" "C_LAYER6_INS_LINE_EN" "C_LAYER6_INS_TEXT_EN" "C_LAYER6_CLUT_SIZE" "C_LAYER6_CLUT_MEMTYPE" "C_LAYER6_FONT_NUM_CHARS" "C_LAYER6_FONT_WIDTH" "C_LAYER6_FONT_HEIGHT" "C_LAYER6_FONT_BPP" "C_LAYER6_FONT_ASCII_OFFSET" "C_LAYER6_TEXT_NUM_STRINGS" "C_LAYER6_TEXT_MAX_STRING_LENGTH" "C_LAYER7_IMEM_SIZE" "C_LAYER7_INS_BOX_EN" "C_LAYER7_INS_LINE_EN" "C_LAYER7_INS_TEXT_EN" "C_LAYER7_CLUT_SIZE" "C_LAYER7_CLUT_MEMTYPE" "C_LAYER7_FONT_NUM_CHARS" "C_LAYER7_FONT_WIDTH" "C_LAYER7_FONT_HEIGHT" "C_LAYER7_FONT_BPP" "C_LAYER7_FONT_ASCII_OFFSET" "C_LAYER7_TEXT_NUM_STRINGS" "C_LAYER7_TEXT_MAX_STRING_LENGTH"
    ::hsi::utils::define_canonical_xpars $drv_handle "xparameters.h" "OSD" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" "C_NUM_LAYERS" "C_LAYER0_TYPE" "C_LAYER1_TYPE" "C_LAYER2_TYPE" "C_LAYER3_TYPE" "C_LAYER4_TYPE" "C_LAYER5_TYPE" "C_LAYER6_TYPE" "C_LAYER7_TYPE" "C_LAYER0_IMEM_SIZE" "C_LAYER0_INS_BOX_EN" "C_LAYER0_INS_LINE_EN" "C_LAYER0_INS_TEXT_EN" "C_LAYER0_CLUT_SIZE" "C_LAYER0_CLUT_MEMTYPE" "C_LAYER0_FONT_NUM_CHARS" "C_LAYER0_FONT_WIDTH" "C_LAYER0_FONT_HEIGHT" "C_LAYER0_FONT_BPP" "C_LAYER0_FONT_ASCII_OFFSET" "C_LAYER0_TEXT_NUM_STRINGS" "C_LAYER0_TEXT_MAX_STRING_LENGTH" "C_LAYER1_IMEM_SIZE" "C_LAYER1_INS_BOX_EN" "C_LAYER1_INS_LINE_EN" "C_LAYER1_INS_TEXT_EN" "C_LAYER1_CLUT_SIZE" "C_LAYER1_CLUT_MEMTYPE" "C_LAYER1_FONT_NUM_CHARS" "C_LAYER1_FONT_WIDTH" "C_LAYER1_FONT_HEIGHT" "C_LAYER1_FONT_BPP" "C_LAYER1_FONT_ASCII_OFFSET" "C_LAYER1_TEXT_NUM_STRINGS" "C_LAYER1_TEXT_MAX_STRING_LENGTH" "C_LAYER2_IMEM_SIZE" "C_LAYER2_INS_BOX_EN" "C_LAYER2_INS_LINE_EN" "C_LAYER2_INS_TEXT_EN" "C_LAYER2_CLUT_SIZE" "C_LAYER2_CLUT_MEMTYPE" "C_LAYER2_FONT_NUM_CHARS" "C_LAYER2_FONT_WIDTH" "C_LAYER2_FONT_HEIGHT" "C_LAYER2_FONT_BPP" "C_LAYER2_FONT_ASCII_OFFSET" "C_LAYER2_TEXT_NUM_STRINGS" "C_LAYER2_TEXT_MAX_STRING_LENGTH" "C_LAYER3_IMEM_SIZE" "C_LAYER3_INS_BOX_EN" "C_LAYER3_INS_LINE_EN" "C_LAYER3_INS_TEXT_EN" "C_LAYER3_CLUT_SIZE" "C_LAYER3_CLUT_MEMTYPE" "C_LAYER3_FONT_NUM_CHARS" "C_LAYER3_FONT_WIDTH" "C_LAYER3_FONT_HEIGHT" "C_LAYER3_FONT_BPP" "C_LAYER3_FONT_ASCII_OFFSET" "C_LAYER3_TEXT_NUM_STRINGS" "C_LAYER3_TEXT_MAX_STRING_LENGTH" "C_LAYER4_IMEM_SIZE" "C_LAYER4_INS_BOX_EN" "C_LAYER4_INS_LINE_EN" "C_LAYER4_INS_TEXT_EN" "C_LAYER4_CLUT_SIZE" "C_LAYER4_CLUT_MEMTYPE" "C_LAYER4_FONT_NUM_CHARS" "C_LAYER4_FONT_WIDTH" "C_LAYER4_FONT_HEIGHT" "C_LAYER4_FONT_BPP" "C_LAYER4_FONT_ASCII_OFFSET" "C_LAYER4_TEXT_NUM_STRINGS" "C_LAYER4_TEXT_MAX_STRING_LENGTH" "C_LAYER5_IMEM_SIZE" "C_LAYER5_INS_BOX_EN" "C_LAYER5_INS_LINE_EN" "C_LAYER5_INS_TEXT_EN" "C_LAYER5_CLUT_SIZE" "C_LAYER5_CLUT_MEMTYPE" "C_LAYER5_FONT_NUM_CHARS" "C_LAYER5_FONT_WIDTH" "C_LAYER5_FONT_HEIGHT" "C_LAYER5_FONT_BPP" "C_LAYER5_FONT_ASCII_OFFSET" "C_LAYER5_TEXT_NUM_STRINGS" "C_LAYER5_TEXT_MAX_STRING_LENGTH" "C_LAYER6_IMEM_SIZE" "C_LAYER6_INS_BOX_EN" "C_LAYER6_INS_LINE_EN" "C_LAYER6_INS_TEXT_EN" "C_LAYER6_CLUT_SIZE" "C_LAYER6_CLUT_MEMTYPE" "C_LAYER6_FONT_NUM_CHARS" "C_LAYER6_FONT_WIDTH" "C_LAYER6_FONT_HEIGHT" "C_LAYER6_FONT_BPP" "C_LAYER6_FONT_ASCII_OFFSET" "C_LAYER6_TEXT_NUM_STRINGS" "C_LAYER6_TEXT_MAX_STRING_LENGTH" "C_LAYER7_IMEM_SIZE" "C_LAYER7_INS_BOX_EN" "C_LAYER7_INS_LINE_EN" "C_LAYER7_INS_TEXT_EN" "C_LAYER7_CLUT_SIZE" "C_LAYER7_CLUT_MEMTYPE" "C_LAYER7_FONT_NUM_CHARS" "C_LAYER7_FONT_WIDTH" "C_LAYER7_FONT_HEIGHT" "C_LAYER7_FONT_BPP" "C_LAYER7_FONT_ASCII_OFFSET" "C_LAYER7_TEXT_NUM_STRINGS" "C_LAYER7_TEXT_MAX_STRING_LENGTH"
}
