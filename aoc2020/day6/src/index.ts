#!/usr/bin/env node
import { readFileSync } from 'fs';
import { initializeLogger } from './utils';
import { getLogger } from 'log4js';

const logger = getLogger();

const main = (): void => {
  const inputData = readFileSync('./input.txt', 'utf-8');
  let sumCounts = 0, sumYes = 0, numInGroup = 0;
  const currentGroup = new Map<string, number>();
  const lines = inputData.split('\n');
  for (let i = 0; i < lines.length; i++) {
    const line = lines[i].trim();
    for (const char of line) {
      const currentCount = currentGroup.get(char);
      currentGroup.set(char, (currentCount ? currentCount : 0) + 1);
    }
    if (line.length > 0) {
      numInGroup++;
    }
    if (line.length === 0 || i === lines.length - 1) {
      for (const val of currentGroup.values()) {
        sumCounts++;
        if (val === numInGroup) {
          sumYes++;
        }
      }
      currentGroup.clear();
      numInGroup = 0;
    }
  }
  logger.info(`part 1: ${sumCounts}`);
  logger.info(`part 2: ${sumYes}`);
};

if (require.main === module) {
  const logger = initializeLogger();
  try {
    main();
  } catch (err) {
    logger.error((err as Error).message);
  }
}

export default main;
