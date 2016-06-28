import subprocess as proc


if __name__ == '__main__':

    cmd = ['python' , './ping.py']

    out = proc.check_output( cmd )

    print out