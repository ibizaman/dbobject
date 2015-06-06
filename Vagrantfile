# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
    config.vm.define "dbobject" do |box|
        box.vm.box = "terrywang/archlinux"
        box.vm.provision :shell, :path => "Vagrantsetup.sh", :privileged => false
        box.vm.provider :virtualbox do |vb|
            vb.name = "dbobject"
            vb.memory = 2048
        end
        box.ssh.forward_agent = true
    end
end
