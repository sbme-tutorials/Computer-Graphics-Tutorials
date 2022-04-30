import argparse
from vtk import *

def convert_dicom_to_vti(dicom_directory, vti_filename):
    """
    Converts a DICOM directory to a VTK XML Image file.

    dicom_directory: DICOM directory
    vti_filename: VTK XML Image file

    >> convert_dicom_to_vti('/home/user/dicom_directory', 'vti_filename.vti')
    """
    reader = vtkDICOMImageReader()
    reader.SetDirectoryName(dicom_directory)
    reader.Update()

    writer = vtkXMLImageDataWriter()
    writer.SetFileName(vti_filename)
    writer.SetInputConnection(reader.GetOutputPort())
    writer.Write()

def main():
    """
    Converts a DICOM directory to a VTK XML Image file.
    """
    argparser = argparse.ArgumentParser(description='Convert DICOM directory to VTK XML Image file.')
    argparser.add_argument('dicom_directory', help='DICOM directory')
    argparser.add_argument('vti_filename', help='VTK XML Image file')
    args = argparser.parse_args()
    convert_dicom_to_vti(dicom_directory= args.dicom_directory.strip() , vti_filename = args.vti_filename.strip())

if __name__=='__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('\n\nExecution interrupted by the user. Exiting...')
        exit(0)
    except Exception as e:
        print('\n\n', e)
        exit(1)
        
