import subprocess as proc


if __name__ == '__main__':

    cmd = ['python' , '/data/local/tmp/ping.py']

    out = proc.check_output( cmd )

    print out