# Delivery Route Optimization System

An intelligent delivery route optimization system that efficiently assigns packages to delivery trucks based on capacity constraints and route proximity using advanced pathfinding algorithms.

## Overview

This system optimizes package delivery for a local delivery company operating three trucks on different routes within a 25x25 grid city map. The application uses A* pathfinding algorithm to calculate optimal routes while considering truck capacity limits and delivery destinations.

## Features

- **Multi-truck route optimization** - Manages 3 delivery trucks with distinct route patterns
- **Capacity management** - Handles weight and volume constraints per truck
- **A* pathfinding algorithm** - Calculates shortest paths avoiding building obstacles
- **Dynamic package assignment** - Assigns packages to trucks based on proximity and available capacity
- **Multiple box sizes** - Supports 0.5, 2, and 5 cubic meter packaging options
- **Real-time route calculation** - Determines optimal diversion paths for deliveries

## Technical Implementation

### Core Algorithm
- **Pathfinding**: A* algorithm with Euclidean distance heuristic
- **Route optimization**: Considers both truck capacity and distance to destination
- **Constraint handling**: Prevents routing through building obstacles
- **Load balancing**: Compares truck capacity as percentage of maximum load

### System Architecture
```
Grid Map (25x25) → Route Analysis → Truck Selection → Path Calculation → Delivery Assignment
```

### Input Processing
- Package weight (1-5000 kg)
- Box size (0.5, 2, or 5 cubic meters)
- Destination coordinates (row-column format)

### Output
- Assigned truck (Blue, Green, or Yellow line)
- Diversion path if required
- "Ships tomorrow" if no truck available

## Build & Test

### Requirements
- Visual Studio (C compiler)
- Windows environment (for automated testing hooks)

### Testing Framework
- **Automated testing** via Git pre-push hooks
- **Unit tests** for individual functions
- **Integration tests** for multi-function workflows
- **Black box & white box testing** methodologies

### Test Automation
Pre-push hook automatically runs test suite:
```bash
# Tests must pass before code can be pushed to repository
# Prevents bugs from entering main codebase
```

## Usage Example

```
Enter shipment weight, box size and destination: 20 2 12L
Ship on BLUE LINE, no diversion

Enter shipment weight, box size and destination: 2000 2 8Y
Ship on GREEN LINE, divert: 7T, 7U, 7V, 7W, 7X, 7Y, 8Y
```

## Algorithm Details

### Distance Calculation
- **Euclidean distance**: √(x² + y²) for initial proximity assessment
- **A* pathfinding**: Handles building obstacles and finds actual shortest path
- **Route analysis**: Examines all points on truck routes to find optimal diversion

### Capacity Management
- **Weight limit**: 5000kg per truck
- **Volume limit**: 250 cubic meters per truck
- **Load comparison**: Uses percentage-based capacity analysis
- **Limiting factor**: System considers both weight and volume constraints

## Development Process

Built using agile methodology with:
- **SCRUM meetings** for progress tracking
- **Jira integration** for issue management
- **Git workflow** with automated testing
- **Comprehensive documentation** and function specifications

## Contributing

1. Create feature branch
2. Implement changes with proper documentation
3. Add corresponding test cases
4. Ensure all tests pass via automated hooks
5. Submit pull request

---

**Built with C and optimized for efficient delivery route management**
