Build Heimdali in development mode
====================================

Development mode means building Heimdali from its source code, typically the
``develop`` branch of heimdali_ Git repository.

Working in development mode consists in iterating in the cycle:

  - Modify source code.
  - Build.
  - Run the test.

without having to run the ``make install`` step.

.. note::

    You may want to use :ref:`ccache_use` to speed-up compilation.

Install dependencies
--------------------

Create a ``conda`` enviromnent named ``heimdali-dev`` containing all dependencies:

.. code-block:: bash

    conda config --add channels http://conda.binstar.org/heimdali
    conda create -n heimdali-dev h5unixpipe itk-heimdali-dbg libinrimage-dbg tclap cmake pip

.. note::

    As ``cmake`` executable is in the conda environment,  it will automatically
    find dependant libraries provided by the conda environment . So using
    ``-DCMAKE_PREFIX_PATH=/path/to/conda/env`` is not required.

.. warning::

    Do not install the ``heimdali`` package in the ``heimdali-dev`` environment,
    as it would conflicts with sources files (from your heimdali git
    repository) you are building.

Activate the conda environment:

.. code-block:: bash

    source activate heimdali-dev
    hash -r
   
Install lettuce:

.. code-block:: bash

    pip install lettuce

Get test datas
--------------------

Get Heimdali data files:

.. code-block:: bash

    git clone https://github.com/heimdali/heimdali-data

Define directories
--------------------

For convenience, define these 3 directories:

+--------------------------+----------------------------------------------------+
| Variable                 | Description                                        |
+==========================+====================================================+
| ``HEIMDALI_SRC_DIR``     | | Heimdali sources (git repo), containing the      |
|                          | | main CMakeLists.txt                              |
+--------------------------+----------------------------------------------------+
| ``HEIMDALI_DATA_DIR``    | | Heimdali data directory (heimdali-data git repo  |
|                          | | cloned above)                                    |
+--------------------------+----------------------------------------------------+
| ``HEIMDALI_WORK_DIR``    | | Directory for temporary files (building sources, |
|                          | | building examples, running tests).               |
+--------------------------+----------------------------------------------------+

For example:

.. code-block:: bash

    cd heimdali
    export HEIMDALI_SRC_DIR=$PWD

    cd heimdali-data
    export HEIMDALI_DATA_DIR=$PWD

    export HEIMDALI_WORK_DIR=/path/to/<heimdali-work-dir>

.. note::

    It may be useful to have ``HEIMDALI_SRC_DIR`` and ``HEIMDALI_WORK_DIR`` if different
    locations. A typical example is having ``HEIMDALI_SRC_DIR`` on a backed-up
    ``NAS`` file system, while ``HEIMDALI_WORK_DIR`` on a local hard disk for speed
    read/write operations.

.. warning::

    The conda environment must be activated and these 3 variables must be
    defined for the sections bellow.

Build Heimdali
--------------------

On Mac OS X your will need to install ``/Developer/SDKs/MacOSX10.6``, and use
it:

.. code-block:: bash

    export MACOSX_DEPLOYMENT_TARGET=10.6

Build heidmali:

.. code-block:: bash

    mkdir -p $HEIMDALI_WORK_DIR/build_debug/src
    cd $HEIMDALI_WORK_DIR/build_debug/src
    cmake -DCMAKE_BUILD_TYPE=Debug $HEIMDALI_SRC_DIR
    make -j 4

Configure examples
--------------------

Heimdali has been built in ``HEIMDALI_WORK_DIR/build_debug/src`` and is not
installed (development mode), we need to specified ``Heimdali`` path to
``cmake``.

.. code-block:: bash

    for example in create_input_image inrimage_read inrimage_write
    do
        mkdir -p $HEIMDALI_WORK_DIR/build_debug/$example
        cd $HEIMDALI_WORK_DIR/build_debug/$example
        cmake \
            -DCMAKE_BUILD_TYPE=Debug \
            -DHEIMDALI_DIR=$HEIMDALI_WORK_DIR/build_debug/src \
            $HEIMDALI_SRC_DIR/example/$example
    done

Example are built latter by ``lettuce``.

Run functional tests
--------------------

Add path to the built executables:

.. code-block:: bash

    export PATH=$HEIMDALI_WORK_DIR/build_debug/src/cmd:$PATH

Run the functional tests:

.. code-block:: bash

    cd $HEIMDALI_SRC_DIR/tests
    lettuce

Writting documentation
====================================


Install Sphinx_ and Doxygen_:

.. code-block:: bash

    sudo apt-get install doxygen
    conda create -n heimdali-doc python=2 sphinx sphinx_rtd_theme
    source activate heimdali-doc

Build the documentation:

.. code-block:: bash
    
    cd doc
    make html

View the documentation:

.. code-block:: bash

    cd doc
    firefox _build/html/index.html

Note that breathe_, a Sphinx extension, is already provided in
``heimdali/doc/ext/breathe``.


Other ``CMake`` usefull variables
====================================

+--------------------------+------------------------------------------------------+
| Variable                 | Description                                          |
+==========================+======================================================+
| ``CMAKE_PREFIX_PATH``    | | Where ``CMake`` will search for dependent          |
|                          | | libraries.                                         |
+--------------------------+------------------------------------------------------+
| ``CMAKE_INSTALL_PREFIX`` | | Where ``CMake`` will install things during         |
|                          | | ``make install``.                                  |
+--------------------------+------------------------------------------------------+


Dependencies
====================================

Here is a summary of Heimdali dependencies, if you want to apply modifications on
it:

+-----------------------------+------------------------+
| sources or homepage         | conda recipe           |
+=============================+========================+
| heimdali_                   | `heimdali recipe`_     |
+-----------------------------+------------------------+
| itk-heimdali_               | `itk-heimdali recipe`_ |
+-----------------------------+------------------------+
| tclap_                      | `tclap recipe`_        |
+-----------------------------+------------------------+
| h5unixpipe_                 | `h5unixpipe recipe`_   |
+-----------------------------+------------------------+
| libinrimage_                | `libinrimage recipe`_  |
+-----------------------------+------------------------+

Conda packages are hosted on `binstar heimdali channel`_.

.. _Sphinx: http://sphinx-doc.org/
.. _Doxygen: www.doxygen.org/
.. _breathe: https://breathe.readthedocs.org
.. _heimdali: https://github.com/heimdali/heimdali
.. _heimdali recipe: https://github.com/heimdali/heimdali/tree/master/conda-recipe
.. _itk-heimdali: https://github.com/heimdali/itk/tree/heimdali
.. _itk-heimdali recipe: https://github.com/heimdali/df-conda-recipe/tree/master/itk-heimdali
.. _tclap: http://tclap.sourceforge.net/
.. _tclap recipe: https://github.com/heimdali/df-conda-recipe/tree/master/tclap
.. _h5unixpipe: https://github.com/heimdali/h5unixpipe
.. _h5unixpipe recipe: https://github.com/heimdali/h5unixpipe/tree/master/conda
.. _libinrimage: http://inrimage.gforge.inria.fr
.. _libinrimage recipe: https://github.com/heimdali/df-conda-recipe/tree/master/libinrimage
.. _binstar heimdali channel: https://binstar.org/heimdali 
