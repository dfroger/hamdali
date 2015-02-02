from subprocess import Popen, PIPE
from os.path import realpath, expandvars
from difflib import ndiff

from lettuce import *

def check_command():
    if world.returncode != 0 or world.stderr != '':
        raise AssertionError, "returncode is %r, stdout is %r, stderr is %r" % (
                world.returncode, world.stdout, world.stderr)

def check_stdout(actual, expected):
    if actual != expected:
        diff = ndiff(actual.splitlines(True), expected.splitlines(True))
        diff = '\n' + ''.join(diff)
        raise AssertionError, "stdout is not as expected " \
            "(- actual, + expected): %s" % (expected, actual, diff,)

@step('I am in the heimdali data directory')
def in_the_data_directory(step):
    world.cwd = world.data_dir

@step('I am in directory (.*)')
def in_the_directory(step,cwd):
    world.cwd = realpath( expandvars(cwd) )

@step('I run the command: (.*)')
def run_the_command(step,cmd):
    p = Popen(cmd, shell=True, stdout=PIPE, stderr=PIPE, cwd=world.cwd)
    world.stdout, world.stderr = p.communicate()
    world.returncode = p.returncode

@step('I see the line in standard output: (.*)')
def i_see_the_line(step,line):
    check_command()
    if not line in world.stdout:
        raise AssertionError, \
            "Expected line: %r in stdout, but stdout is: %r" % (
                line,world.stdout)

@step(u'Then I see the standard output:')
def then_i_get_the_standard_output(step):
    expected_stdout = step.multiline 
    check_command()
    check_stdout(world.stdout, expected_stdout)

def factorial(number):
    return 1
