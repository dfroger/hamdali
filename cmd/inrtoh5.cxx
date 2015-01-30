#include <stdlib.h>
#include <string.h>
#include <iostream>

#include <tclap/CmdLine.h>

#include <itkImage.h>
#include <itkINRImageIOFactory.h>
#include <itkImageFileReader.h>
#include "itkImageFileWriter.h"

// author: <david.froger@inria.fr>
// usage: Please see 'help' function bellow.

using namespace std;

///////////////////////////////////////////////////////////////////////////
// Function to print help message.
///////////////////////////////////////////////////////////////////////////

int main( int argc, char ** argv )
{


  try {


    ///////////////////////////////////////////////////////////////////////////
    // Parse command line arguments.
    ///////////////////////////////////////////////////////////////////////////


    TCLAP::CmdLine cmd("Convert INRimage image to HDF5 image.", ' ', "0.0");

    // input.inr
    TCLAP::UnlabeledValueArg<string> inputFilenameArg("inputFilename", 
        "INRimage image.",true,"","inputFilename",cmd);

    // output.hdf5
    TCLAP::UnlabeledValueArg<string> outputFilenameArg("outputFilename", 
        "HDF5 image.",true,"","outputFilename",cmd);

    cmd.parse(argc,argv);

    string inputFilename = inputFilenameArg.getValue();
    string outputFilename = outputFilenameArg.getValue();



   ///////////////////////////////////////////////////////////////////////////
   // Read and write image
   ///////////////////////////////////////////////////////////////////////////


   // Put our INRimage reader in the list of readers ITK knows.
   itk::ObjectFactoryBase::RegisterFactory( itk::INRImageIOFactory::New() ); 

   // Image.
   typedef float          PixelType;
   const   unsigned int   ImageDimension = 3;
   typedef itk::VectorImage<PixelType, ImageDimension> ImageType;

   // Reader.
   typedef itk::ImageFileReader< ImageType >  ReaderType;
   ReaderType::Pointer reader = ReaderType::New();
   reader->SetFileName( inputFilename  );

   // Writer.
   typedef itk::ImageFileWriter<ImageType>  WriterType;
   WriterType::Pointer writer = WriterType::New();
   writer->SetFileName(outputFilename);

   // Connect reader to writer.
   writer->SetInput( reader->GetOutput() );

   // Update pipeline.
   writer->Update();

  }

  // Command line parser.
  catch (TCLAP::ArgException &e) { 
      cerr << "inr2hdf5: ERROR: " << e.error() << " for arg " << e.argId() << endl;
  }

  return 0;
}
