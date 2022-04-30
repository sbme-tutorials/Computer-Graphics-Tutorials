from vtk import *
import argparse

class myVtkInteractorStyleImage(vtkInteractorStyleImage):
    """
    Customize the mouse wheel event to move the slice forward or backward.
    """
    def __init__(self, imageViewer, orientation) -> None:
        """
        Initialize the class.
        """
        super().__init__()
        self.imageViewer = imageViewer
        self.imageViewer.SetSliceOrientation(orientation)
        self.min_slice = imageViewer.GetSliceMin()
        self.max_slice = imageViewer.GetSliceMax()
        self.slice = self.max_slice//2
        self.AddObserver("MouseWheelForwardEvent", self.moveSliceForward)
        self.AddObserver("MouseWheelBackwardEvent", self.moveSliceBackward)

    def moveSliceForward(self, obj, event):
        """
        Move the slice forward.
        """
        self.slice += 1
        if self.slice > self.max_slice:
            self.slice = self.max_slice
        self.imageViewer.SetSlice(self.slice)
        self.imageViewer.Render()
    
    def moveSliceBackward(self, obj, event):
        """
        Move the slice backward.
        """
        self.slice -= 1
        if self.slice < self.min_slice:
            self.slice = self.min_slice
        self.imageViewer.SetSlice(self.slice)
        self.imageViewer.Render()


def view_dicom_series(dicom_directory, orientation):
    """
    Visualize the DICOM series and scroll through the slices.

    directory: DICOM directory
    orientation: AXIAL, CORONAL, or SAGITTAL
    """
    # Read all the dicom files in the specified directory
    reader = vtkDICOMImageReader()
    reader.SetDirectoryName(dicom_directory)
    reader.Update()

    # Visualize
    imageViewer = vtkImageViewer2()
    imageViewer.SetSliceOrientation(orientation)
    imageViewer.SetInputConnection(reader.GetOutputPort())
    imageViewer.SetSlice(imageViewer.GetSliceMax()//2)

    # create interactor with our own style
    renderWindowInteractor = vtkRenderWindowInteractor()
    imageViewer.SetupInteractor(renderWindowInteractor)
    
    # create our own style
    ownStyle = myVtkInteractorStyleImage(imageViewer, orientation)
    renderWindowInteractor.SetInteractorStyle(ownStyle)
    imageViewer.Render()
    renderWindowInteractor.Start()

    
def get_view_idx(orientation):
    """
    Get the view index for the specified orientation.
    """
    if orientation == "AXIAL":
        return 2
    elif orientation == "CORONAL":
        return 1
    elif orientation == "SAGITTAL":
        return 0
    else:
        raise Exception("Invalid orientation")

if __name__ == "__main__":
    """
    Parse the command line arguments. and run the visualization of the DICOM series.
    """
    arg_parser = argparse.ArgumentParser(description='Visualize DICOM directory.')
    arg_parser.add_argument('dicom_directory', help='DICOM directory')
    arg_parser.add_argument('orientation', help='View plane AXIAL, CORONAL, or SAGITTAL')
    args = arg_parser.parse_args()
    orientation_idx = get_view_idx(args.orientation)
    view_dicom_series(dicom_directory= args.dicom_directory.strip(), orientation=orientation_idx)