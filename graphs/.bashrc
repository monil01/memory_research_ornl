# .bashrc

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

# Uncomment the following line if you don't like systemctl's auto-paging feature:
# export SYSTEMD_PAGER=

# User specific aliases and functions
alias rdp='xfreerdp /u:mmonil  /f /v:128.223.202.161'
#alias rdp1='xfreerdp -u mmonil -f mmonil.nic.uoregon.edu'
#alias rdp='xfreerdp -u mmonil -f mmonil.nic.uoregon.edu'
alias cerberus='ssh -Y cerberus.nic.uoregon.edu'
alias nic='ssh -Y cerberus.nic.uoregon.edu'
alias motion='ssh -Y cerberus.nic.uoregon.edu'
alias delphi='ssh -Y cerberus.nic.uoregon.edu;'
alias cori='ssh -Y cori.nersc.gov;'
alias excl='ssh -Y mmonil@login.excl.ornl.gov'
alias oswald01='ssh -Y -t mmonil@login.excl.ornl.gov " ssh -t oswald01"'
alias quad00='ssh -Y -t mmonil@login.excl.ornl.gov " ssh  -t quad00"'
alias apachepass='ssh -Y -t mmonil@login.excl.ornl.gov " ssh  -t apachepass"'
alias jupiter='ssh -t cerberus " ssh -t jupiter"'
alias pegasus='ssh -t cerberus " ssh -t pegasus"'
alias explorer='ssh -t cerberus " ssh -t explorer"'
alias godzilla='ssh -t cerberus " ssh -t godzilla "'



. /home/mmonil/spack/share/spack/setup-env.sh
#spack load -r cmake

export GOPATH=${HOME}/go
export PATH=/usr/local/go/bin:${PATH}:${GOPATH}/bin
alias dirs="dirs -v"
