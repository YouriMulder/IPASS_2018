.PHONY: clean All

All:
	@echo "----------Building project:[ test -  ]----------"
	@cd "test" && "$(MAKE)" -f  "test.mk"
clean:
	@echo "----------Cleaning project:[ test -  ]----------"
	@cd "test" && "$(MAKE)" -f  "test.mk" clean
