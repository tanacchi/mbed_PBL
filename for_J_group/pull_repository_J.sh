git clone https://github.com/tanacchi/mbed_PBL.git
cd mbed_PBL
git config core.sparsecheckout true
echo for_J_group/ > .git/info/sparse-checkout
git read-tree -m -u HEAD

