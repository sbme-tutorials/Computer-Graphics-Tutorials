#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Apr  6 14:05:05 2019

@author: eslam
"""

import sys
from PyQt5.QtWidgets import QMainWindow, QApplication
from slider import Ui_MainWindow
from vtk.qt.QVTKRenderWindowInteractor import QVTKRenderWindowInteractor
import vtk

dataDir = 'headsq/quarter'
surfaceExtractor = vtk.vtkContourFilter()


def slider_SLOT(val):
    surfaceExtractor.SetValue(0, val)
    iren.update()
    
    
class AppWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ui.horizontalSlider.valueChanged.connect(slider_SLOT)
        self.show()  
    



def vtk_rendering():
    renWin = iren.GetRenderWindow()
    aRenderer = vtk.vtkRenderer()
    renWin.AddRenderer(aRenderer)

    
    # Read Dataset using vtkVolume16Reader 
    v16 = vtk.vtkVolume16Reader()
    v16.SetDataDimensions(64, 64)
    v16.SetDataByteOrderToLittleEndian()
    v16.SetFilePrefix(dataDir)
    v16.SetImageRange(1, 93)
    v16.SetDataSpacing(3.2, 3.2, 1.5)
    
    # An isosurface, or contour value of 500 is known to correspond to the
    surfaceExtractor.SetInputConnection(v16.GetOutputPort())
    surfaceExtractor.SetValue(0, 500)
    surfaceNormals = vtk.vtkPolyDataNormals()
    surfaceNormals.SetInputConnection(surfaceExtractor.GetOutputPort())
    surfaceNormals.SetFeatureAngle(60.0)
    surfaceMapper = vtk.vtkPolyDataMapper()
    surfaceMapper.SetInputConnection(surfaceNormals.GetOutputPort())
    surfaceMapper.ScalarVisibilityOff()
    surface = vtk.vtkActor()
    surface.SetMapper(surfaceMapper)
    
    aCamera = vtk.vtkCamera()
    aCamera.SetViewUp(0, 0, -1)
    aCamera.SetPosition(0, 1, 0)
    aCamera.SetFocalPoint(0, 0, 0)
    aCamera.ComputeViewPlaneNormal()
    
    aRenderer.AddActor(surface)
    aRenderer.SetActiveCamera(aCamera)
    aRenderer.ResetCamera()
    
    aRenderer.SetBackground(0, 0, 0)
    
    aRenderer.ResetCameraClippingRange()
    
    # Interact with the data.
    iren.Initialize()
    renWin.Render()
    iren.Start()
    iren.show()
     

app = QApplication(sys.argv)
# The class that connect Qt with VTK
iren = QVTKRenderWindowInteractor()
w = AppWindow()
vtk_rendering()
w.show()
sys.exit(app.exec_())
# Start the event loop.
