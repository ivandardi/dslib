# https://martinhh.github.io/2014/08/27/hosting-doxygen-as-github-page/

# Generate Doxygen
doxygen doxygen

# Change into the gh-pages branch
cd html

# Committing and pushing the new Doxygen
git add .
git commit -m "Updating Doxygen."
git push -u origin gh-pages

# Committing the changes to the master branch
cd ../..
add .
commit -m "Committing Doxygen update to master branch."
push -u origin master