# Contributing

In order to maintain a clean and efficient repository, all contributors are expected to follow all of the following style guides and conventions.

## Versioning

This project uses [Semantic Versioning](https://semver.org/) (MAJOR.MINOR.PATCH) to tag releases.

 - MAJOR: Major changes that are not backwards compatible
 - MINOR: Features that are backwards compatible
 - PATCH: Bug fixes and other small changes that are backwards compatible
 
Releases are tagged and follow the format: `v1.0.0`, `v2.3.4`, etc.

Files containing the current version are updated by the project's CI chain automatically.

## Code Style

This project uses [Google's C++ code style](https://google.github.io/styleguide/cppguide.html) . All rules follow this style guide, and are enforced with a linting step in the CI pipeline. All code changes are expected to follow this guide, but exceptions will be evaluated on a case-by-case basis during the pull request review process.

### Example

```c++
#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include "shape.hpp"

namespace project_name {

class Rectangle : public Shape {
  public:
    Rectangle() : width_(0.0), height_(0.0) { };
    Rectangle(float width, float height) : width_(width), height_(height) { };
    float area() { return width_ * height_; };

  private:
    float width_;
    float height_;
}

}   // namespace project_name

#endif 	// RECTANGLE_HPP_
```

## Branches

This project uses [Trunk Based Development](https://trunkbaseddevelopment.com/). All work is done on short-lived branches that branch off of the trunk or 'main' branch, and is then merged back into the trunk. The names of all branches are standardized and follow the [Conventional Branch](https://conventional-branch.github.io) naming convention. All branches use only lowercase letters, numbers, and hyphens to separate words.

### Long-lived Branches
| Branch | Purpose |
|--|--|
| `main` | Target branch of all development work. |
| `release/x.y` | Maintenance branches for released minor versions. Bug fixes are all cherry-picked from main. |

### Short-lived Branches

All short-lived branches are structured as: `<type>/<description>`. The descriptions start with the corresponding issue number.

| Type | Purpose |
|--|--|
| `feature/` | Features that change code functionality. |
| `bugfix/` | Bug fixes. |
| `chore/` | Non-functional tasks such as dependency or documentation changes. |

### Examples

- `release/3.2.1`
- `feature/123-new-feature-title`
- `bugfix/456-code-issue`

## Commit Messages

This project uses [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) for all commits. Any commits not following this convention must be renamed or squashed before they will be merged into the main branch. This is to allow for automated changelog creation and semantic versioning.

All commits implement the following format: 
```
<type>: <description>

<optional body>

<optional footer(s)>
```
The commit type is used to designate what changes the commit contains. Any number of types can be contained in one commit, but each must get its own line. The type must be one of the following:

- `build`: Changes that affect how the project or dependencies are built
- `ci`: Changes to the CI pipeline configuration and scripts
- `docs`: Changes to the documentation
- `feat`: A new feature
- `fix`: Any fix to existing code
- `perf`: A change that improves the performance of existing code
- `refactor`: A change that does not alter code functionality, but reorganizes it
- `style`: A change to the formatting of the code but not the functionality
- `test`: Any change to new or existing tests

An exclamation point (`!`) after the commit type indicates a breaking change, which correlates to a major version change.

Following the commit type is a short description of the related changes to the project.

After the list of type-description entries is the optional body of the commit message. This provides a longer and more detailed description of changes in the commit. Each paragraph is separated by a blank line.

Following the description is the commit message footer. If the commit fulfills a registered issue, the issue is referenced in the `Refs` footer.

### Examples

```
feat: add new backwards-compatible feature
test: add new unit test for new feature

Add a new feature that fulfills requested functionality.

Refs: #123
```

```
fix: prevent segfault on function call

Fix a nullptr reference in function in file.cpp.

Refs: #456
```

```
feat!: add new backwards-incompatible feature
docs: add documentation for new feature
test: add unit tests for new feature
```

## Merging

All code changes must go from a short-lived branch, made specifically for those changes, to the trunk branch. In order to merge, all changes must go through a **pull request**. The pull request should target `main`. This project uses **squash merging** to keep the git history clean. All commits to be merged must fulfill the conventional commit style described above.

## Example Workflow

The following is an example of how changes are made and added to the project.

1. **Create a branch**

	When it's determined that a change is to be made, a branch is created. This can be done manually or through the project repo's web page.

	```
	user@localhost:~$ git checkout main
	user@localhost:~$ git checkout -b feature/123-new-feature
	```

	Pull requests can optionally be created once the branch has been created. This will allow for regular checks provided by the CI pipeline. If a pull request is created before the branch is ready to be merged into the trunk, the pull request title must be prefixed with `WIP:` to signify that it is a 'Work In Progress'.

2.  **Make changes**

	Make necessary changes to the code, tests, documentation, or other aspects of the project.

3.  **Commit changes**

	Add the changes to the code and commit the changes, writing a commit message in compliance with the conventions described in [the previous section](#commit-messages).

	```
	user@localhost:~$ git commit -m "feat: add new feature" -m "" -m "This commit adds a new feature."
	```

4. **Push commits**

	Push the changes to the remote repository where the project is managed.

	```
	user@localhost:~$ git push origin feature/123-new-feature
	```

5.  **Pull Request**

	If not done previously, create a pull request. Creating a pull request will cause the CI pipeline to begin processing the branch and examining it for a merge into the trunk. There are many steps that must execute successfully for a branch to be considered ready for merging.

	[TBD]

	Once the pull request is accepted, the changes will be merged into the trunk.
