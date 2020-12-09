#!/usr/bin/env node
import { readFileSync } from 'fs';
import { initializeLogger } from './utils';
import { getLogger } from 'log4js';

const logger = getLogger();

const targetBag = 'shiny gold';

interface InvertedData {
  bag: string;
  count: number;
}

const main = (): void => {
  const inputData = readFileSync('./input.txt', 'utf-8');
  const invertedBags: Record<string, InvertedData[]> = {};
  const sumBags = 0;
  for (let line of inputData.split('\n')) {
    line = line.trim();
    const splitContain = line.split('contain').map(elem => elem.trim());
    if (splitContain.length !== 2) {
      logger.info(`invalid line ${line}`);
      continue;
    }
    const splitBagStr = 'bag';
    const currentBag = splitContain[0].split(splitBagStr)[0].trim();
    const keys = splitContain[1].split(',').map(elem => {
      return elem.trim().split(splitBagStr)[0].trim();
    });
    for (const key of keys) {
      const currKeyCount = 0; // TODO - fix this
      if (!(key in invertedBags)) {
        invertedBags[key] = [];
      }
      invertedBags[key].push({
        bag: currentBag,
        count: currKeyCount
      });
    }
  }
  const elementsToCheck: string[] = [targetBag];
  logger.info(elementsToCheck);

  logger.info(`part 1: ${sumBags}`);
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
