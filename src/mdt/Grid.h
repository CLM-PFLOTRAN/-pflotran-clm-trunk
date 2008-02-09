#ifndef GRID_H_
#define GRID_H_

#include "include/petsc.h"
#include "include/petscvec.h"
#include "include/petscmat.h"
#include "include/petscis.h"

#include "BoundarySet.h"
#include "Globals.h"
#include "GridCell.h"
#include "GridVertex.h"
#include "Source.h"
#include "StructuredGrid.h"

class Grid {
  
public:

  Grid();
  Grid(PetscInt nx, PetscInt ny, PetscInt nz);
  virtual ~Grid();

  void nullifyArrays();
  void createStructured(PetscInt nx, PetscInt ny, PetscInt nz);
  void createDA(PetscInt ndof);
//  void computeConnectivity();
  void computeCellMapping();
  void computeVertexMapping();
  void setUpCells();
  void setUpVertices();
  void mapVerticesToCells();
  void printISLocalToGlobalMapping();
  void printAO();
  void addBoundarySet(BoundarySet *new_set);
//  void printConnectivity();
  void printCells();
  void printVertices();
//  void addBoundaryConnection(PetscInt is, PetscInt ie, PetscInt js, PetscInt je, 
//                             PetscInt ks, PetscInt ke, 
//                            char *face, char *type, PetscReal scalar);
  void addSource(PetscInt is, PetscInt ie, PetscInt js, PetscInt je, 
                 PetscInt ks, PetscInt ke, char *type, PetscReal scalar);

  void getVectorNatural(Vec *v);
  void getVectorLocal(Vec *v);
  void getVectorGlobal(Vec *v);

  void globalToNatural(Vec global, Vec natural);
//  BoundaryConnection *getBoundaryConnections();
  Source *getSources();

  PetscInt getNumberOfCellsGlobal();
  PetscInt getNumberOfCellsGhosted();
  PetscInt getNumberOfCellsLocal();

  PetscInt getNumberOfVerticesGlobal();
  PetscInt getNumberOfVerticesGhosted();
  PetscInt getNumberOfVerticesLocal();

  PetscInt getNx();
  PetscInt getNy();
  PetscInt getNz();
  PetscInt getN();

  void sendFlag(PetscInt *flag, PetscInt direction);
  void receiveFlag(PetscInt *flag, PetscInt direction);
  
  void getCorners(PetscInt *xs, PetscInt *ys, PetscInt *zs, 
                  PetscInt *nx, PetscInt *ny, PetscInt *nz);
  void getGhostCorners(PetscInt *xs, PetscInt *ys, PetscInt *zs, 
                       PetscInt *nx, PetscInt *ny, PetscInt *nz);

  PetscReal getDx(PetscInt i);
  PetscReal getDy(PetscInt j);
  PetscReal getDz(PetscInt k);
  PetscReal *getOriginPtr();
  PetscReal getRotationDegrees();
  Vec getGridCellMaterialIDs();
  Vec getGridCellActivities();
  void setGridSpacing(PetscReal *dx, PetscReal *dy, PetscReal *dz);
  void setGridSpacing(PetscReal dx, PetscReal dy, PetscReal dz);
  void setLocalGridSpacing();
  void setOrigin(PetscReal x, PetscReal y, PetscReal z);
  void setRotation(PetscReal r);
  void computeCoordinates();
  void addBoundarySet();
  BoundarySet *getBoundarySet(char *name);

  void convertLocalCellDataGtoN(PetscInt *data);
  void convertLocalCellDataGtoN(PetscReal *data);
  PetscInt getVertexIdsNaturalLocal(PetscInt **natural_ids);
  PetscInt getVertexCoordinatesNaturalLocal(PetscReal **coordinates, 
                                            PetscInt direction);
  PetscInt *getCellMaterialIds();
  PetscInt *getCellIds();
  PetscInt *getCellIdsNatural();
  PetscInt *getCellIdsNatural1Based();
  PetscInt *getCellVertexIds(PetscInt ivert);

  void zeroGridCellFlags();

  PetscInt num_cells_global;
  PetscInt num_cells_local;
  PetscInt num_cells_ghosted;
//  PetscInt num_connections;
  PetscInt *cell_mapping_local_to_ghosted;
  PetscInt *cell_mapping_ghosted_to_local;
  PetscInt *cell_mapping_ghosted_to_natural;
  GridCell *cells;

  PetscInt num_vertices_global;
  PetscInt num_vertices_local;
  PetscInt num_vertices_ghosted;
  PetscInt *vertex_mapping_local_to_ghosted;
  PetscInt *vertex_mapping_ghosted_to_local;
  PetscInt *vertex_mapping_ghosted_to_natural;
  GridVertex *vertices;
//  GridConnection *connections;

  BoundarySet *boundary_sets;
  
  IS inactive_is;

private:
  PetscErrorCode ierr;
  StructuredGrid *structuredGrid;

};

#endif /*GRID_H_*/
