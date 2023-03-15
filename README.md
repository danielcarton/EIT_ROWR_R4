# EIT_ROWR_R4

## How to share Wi-Fi with Jetson
### On Windows
- go to 'view network connections'
- Make note of the ethernet connection of the Jetson. It is marked Corechip SR9900...
- right click your Wi-Fi connections and click 'Properties'
- Go to 'Sharing' tab
- Under 'Internet Connection Sharing' check 'Allow other network users to connect through this computer's insternet connection'.
- Select the ethernet connection of the Jetson (e.g. Ethernet 3).
- Click 'Ok'

## How to ssh
- Use Putty to enter Jetson and call 'ip addr show'
- copy the ip address under 'eth0'
- in terminal execute 'ssh eit-rowr-r4@<ip_addr>'

## How to spin up the container
- Navigate to where the Dockerfile and docker-compose.yml are located in the Jetson this is 'Desktop/EIT-Work/EIT_ROWR_R4/'
- 'sudo docker-compose up -d ghost_trawler'
- -d is 'detatched', meaning it will execute the service in the background.
The container is now running in the background and has a shared volume, the src folder. This means changes inside the src folder are synced between the host and the container are sync'ed.
- If you have never built the image before, the image will build, but give you a warning. If not, then do 'sudo docker-compose up -d --build ghost_trawler' instead.

You can now enter the container by executing 'sudo docker-compose exec ghost_trawler /bin/bash'