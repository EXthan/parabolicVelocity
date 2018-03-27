/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2016 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::parabolicVelocityFvPatchVectorField

Group
    grpInletBoundaryConditions

Description
    This boundary condition describes an inlet vector boundary condition in
    cylindrical co-ordinates given a central axis, central point, R, axial
    and radial velocity.

Usage
    \table
        Property      | Description             | Required    | Default value
        axis          | axis of rotation        | yes         |
        centre        | centre of rotation      | yes         |
        Ubar          | mean velocity [m/s]     | yes         |
        R             | tube radius             | yes         |
        value         | initial value [m/s]     | yes         |
    \endtable

    Example of the boundary condition specification:
    \verbatim
    <patchName>
    {
        type            parabolicVelocity;
        axis            (1 0 0);
        centre          (0 0 0);
        Ubar            constant 1;
        R               constant 1;
        value           uniform (0 0 0);
    }
    \endverbatim

Note
    The \c Ubar, \c radialVelocity and \c R entries are Function1
    types, able to describe time varying functions.  The example above gives
    the usage for supplying constant values.

See also
    Foam::fixedValueFvPatchField
    Foam::Function1Types

SourceFiles
    parabolicVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#ifndef parabolicVelocityFvPatchVectorField_H
#define parabolicVelocityFvPatchVectorField_H

#include "fixedValueFvPatchFields.H"
#include "Function1.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
/*---------------------------------------------------------------------------*\
         Class parabolicVelocityFvPatchVectorField Declaration
\*---------------------------------------------------------------------------*/

class parabolicVelocityFvPatchVectorField
:
    public fixedValueFvPatchVectorField
{
    // Private data

        //- Central point
        const vector centre_;

        //- Axis
        const vector axis_;

        //- Axial velocity
        autoPtr<Function1<scalar>> Ubar_;

        //- R
        autoPtr<Function1<scalar>> R_;


public:

   //- Runtime type information
   TypeName("parabolicVelocity");


   // Constructors

        //- Construct from patch and internal field
        parabolicVelocityFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        parabolicVelocityFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //  flowRateInletVelocityFvPatchVectorField
        //  onto a new patch
        parabolicVelocityFvPatchVectorField
        (
            const parabolicVelocityFvPatchVectorField&,
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        parabolicVelocityFvPatchVectorField
        (
            const parabolicVelocityFvPatchVectorField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchVectorField> clone() const
        {
            return tmp<fvPatchVectorField>
            (
                new parabolicVelocityFvPatchVectorField(*this)
            );
        }

        //- Construct as copy setting internal field reference
        parabolicVelocityFvPatchVectorField
        (
            const parabolicVelocityFvPatchVectorField&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchVectorField> clone
        (
            const DimensionedField<vector, volMesh>& iF
        ) const
        {
            return tmp<fvPatchVectorField>
            (
                new parabolicVelocityFvPatchVectorField(*this, iF)
            );
        }


    // Member functions

        //- Update the coefficients associated with the patch field
        virtual void updateCoeffs();

        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
