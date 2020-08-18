# ansi_iso_accuracy_test

[![Build Status](http://sdk-jenkins-1u/view/Jobs/job/IEngine/job/ANSI-ISO%20Accuracy%20Test/job/master/badge/icon)](http://sdk-jenkins-1u/view/Jobs/job/IEngine/job/ANSI-ISO%20Accuracy%20Test/job/master/)

Accuracy and performance benchmark tool for Innovatrics' ANSI&ISO biometric SDK.

## Getting Started

These instructions will get you a copy of the project up and running on your
local machine for development and testing purposes.

### Prerequisites

This project is using [conan.io](https://docs.conan.io/en/latest/) for
dependencies management, [cmake](https://cmake.org/cmake/help/latest/) for build
generation.

Get the source, create a build directory and jump into it:

```bash
git clone https://github.com/tomas-krupa/ansi_iso_accuracy_test.git
cd ansi_iso_accuracy_test
mkdir _build && cd _build
```

Invoke conan to install dependencies and configure your build:

```bash
conan install -u -b outdated ..
```

To build the library, run conan build:

```bash
conan build ..
```

Preceding commands build the library localy and don't install the package to
local conan cache. To create and install the package to local cache, run conan
create in source directory:

```bash
conan create . user/channel
```

For more information on conan usage, see the [conan
documentation](https://docs.conan.io/en/latest/).

## Contributing

Please read
[CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for
details on our code of conduct, and the process for submitting pull requests to
us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available,
see the [tags on this repository](https://github.com/your/project/tags).

## Authors

* **Tomas Krupa** - *Initial work* -
  [Innovatrics](https://git.ba.innovatrics.net/users/tomas.krupa)

## License

This project is licensed under the [Apache 2.0 License](./LICENSE)
