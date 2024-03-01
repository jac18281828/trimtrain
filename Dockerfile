FROM ghcr.io/jac18281828/cppdev:latest

ARG PROJECT=trimtrain
WORKDIR /workspaces/${PROJECT}

COPY --chown=jac:jac . .

ARG BUILD=build
RUN mkdir -p ${BUILD} && chown -R jac:jac ${BUILD}

ENV USER=jac
USER jac


ARG TYPE=DEBUG

#build
ENV MAKEFLAGS=-j8
RUN cmake -H. -B${BUILD} -DPROJECT_NAME=${PROJECT} -DCMAKE_BUILD_TYPE=${TYPE} -DCMAKE_VERBOSE_MAKEFILE=on -Wno-dev "-GUnix Makefiles"
RUN cmake --build ${BUILD} --verbose --config ${TYPE}
ENV CTEST_OUTPUT_ON_FAILURE=1
RUN (cd ${BUILD} && ctest --verbose --output-on-failure)
ENV PROJECT_NAME=${PROJECT}
CMD build/main
