import subprocess
import sys
import time


def run_traceroute(hostname):
    try:
        # Run traceroute command with a timeout of 20 seconds
        result = subprocess.run(['traceroute', '-w', '20', hostname], capture_output=True, text=True, timeout=20)

        # Check if traceroute terminated successfully
        if result.returncode == 0:
            print(f"{len(result.stdout.strip().splitlines()) - 5}  hops to {hostname}")
        else:
            print("Traceroute: failed")
    except subprocess.TimeoutExpired:
        print("Traceroute: failed (timeout)")


# Prompt user for a host name
hostname = input("Enter a server name:\n")

# Call the function to run traceroute
run_traceroute(hostname)
