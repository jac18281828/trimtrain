FROM ghcr.io/jac18281828/cppdev:latest

ARG PROJECT=trimtrain
WORKDIR /workspaces/${PROJECT}

COPY --chown=jac:jac . .

ENV USER=jac
USER jac

ARG BUILD=build
ARG TYPE=DEBUG

RUN mkdir -p ${BUILD}
#build
ENV MAKEFLAGS=-j8
RUN cmake -H. -B${BUILD} -DPROJECT_NAME=${PROJECT} -DCMAKE_BUILD_TYPE=${TYPE} -DCMAKE_VERBOSE_MAKEFILE=on -Wno-dev "-GUnix Makefiles"
RUN cmake --build ${BUILD} --verbose --config ${TYPE}
ENV CTEST_OUTPUT_ON_FAILURE=1
RUN (cd ${BUILD} && ctest)
ENV PROJECT_NAME=${PROJECT}
CMD build/main
