PROJECTS=collections geometry commands render apps

TESTS=$(filter-out commands render,$(PROJECTS))

all: $(PROJECTS)

define PROJECT_RULE
.PHONY: $(1) test-$(1) clean-$(1)
$(1):
	make -C ./$(1) -k

test-$(1):
	make -C ./$(1) -k test

run-test-$(1):
	make -C ./$(1) -k run-test

clean-$(1):
	make -C ./$(1) -k clean
endef

$(foreach P,$(PROJECTS),$(eval $(call PROJECT_RULE,$(P))))

test: all $(foreach T,$(TESTS),test-$(T))

run-test: test $(foreach T,$(TESTS),run-test-$(T))

clean: $(foreach P,$(PROJECTS),clean-$(P))
